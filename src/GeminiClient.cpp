#include "GeminiClient.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QBuffer>

GeminiClient::GeminiClient(const QString& apiKey, QObject *parent)
    : QObject(parent), m_apiKey(apiKey)
{
    m_networkManager = new QNetworkAccessManager(this);
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &GeminiClient::onReplyFinished);
}

void GeminiClient::solveEquation(const QImage& canvasImage)
{
    if (m_apiKey.isEmpty()) {
        emit errorOccurred("API Key is not set. Please set the GEMINI_API_KEY environment variable.");
        return;
    }

    QString base64Image = imageToBase64(canvasImage);
    QByteArray jsonData = buildJsonPayload(base64Image);

    QString url = "https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-pro-latest:generateContent?key=" + m_apiKey;
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    m_networkManager->post(request, jsonData);
}

QString GeminiClient::imageToBase64(const QImage& image) const
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    return byteArray.toBase64();
}

QByteArray GeminiClient::buildJsonPayload(const QString& base64Image) const
{
    QJsonObject textPart;
    textPart["text"] = "Give the answer to this math equation. Only respond with the answer. Only respond with numbers. NEVER Words. Only answer unanswered expressions. Look for an equal sign with nothing on the right of it. If it has an answer already, DO NOT ANSWER it.";

    QJsonObject inlineData;
    inlineData["mime_type"] = "image/png";
    inlineData["data"] = base64Image;

    QJsonObject imagePart;
    imagePart["inline_data"] = inlineData;

    QJsonArray partsArray;
    partsArray.append(textPart);
    partsArray.append(imagePart);

    QJsonObject content;
    content["parts"] = partsArray;

    QJsonArray contentsArray;
    contentsArray.append(content);

    QJsonObject root;
    root["contents"] = contentsArray;

    return QJsonDocument(root).toJson();
}

void GeminiClient::onReplyFinished(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        emit errorOccurred("Network Error: " + reply->errorString());
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObj = jsonDoc.object();

    if (jsonObj.contains("error")) {
        QString errorMessage = jsonObj["error"].toObject()["message"].toString();
        emit errorOccurred("API Error: " + errorMessage);
    } else if (jsonObj.contains("candidates")) {
        QJsonArray candidates = jsonObj["candidates"].toArray();
        if (!candidates.isEmpty()) {
            QJsonObject firstCandidate = candidates[0].toObject();
            QJsonObject content = firstCandidate["content"].toObject();
            QJsonArray parts = content["parts"].toArray();
            if (!parts.isEmpty()) {
                QString answer = parts[0].toObject()["text"].toString().trimmed();
                emit solutionReceived(answer);
            } else {
                emit errorOccurred("Could not parse solution from API response.");
            }
        }
    } else {
        emit errorOccurred("Invalid API response format.");
    }

    reply->deleteLater();
}