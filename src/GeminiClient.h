#pragma once

#include <QObject>
#include <QString>
#include <QImage>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class GeminiClient : public QObject
{
    Q_OBJECT

public:
    // Constructor takes the API key for authentication.
    explicit GeminiClient(const QString& apiKey, QObject *parent = nullptr);

    // Public method to initiate the math solving request.
    void solveEquation(const QImage& canvasImage);

signals:
    // Emitted when the API successfully returns a solution.
    void solutionReceived(const QString& answer);

    // Emitted when any error occurs (network, API, parsing).
    void errorOccurred(const QString& errorString);

private slots:
    // Slot to handle the completed network reply.
    void onReplyFinished(QNetworkReply* reply);

private:
    // Converts a QImage to a Base64 encoded string.
    QString imageToBase64(const QImage& image) const;

    // Constructs the JSON payload for the Gemini API.
    QByteArray buildJsonPayload(const QString& base64Image) const;

    QString m_apiKey;
    QNetworkAccessManager* m_networkManager;
};