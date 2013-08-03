/*
 * NetworkManager.hpp
 *
 *  Created on: Aug 3, 2013
 *      Author: Yaxi Ye
 */

#ifndef NETWORKMANAGER_HPP_
#define NETWORKMANAGER_HPP_

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkSession>
#include <QtNetwork/QNetworkConfigurationManager>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QObject>
#include <QUrl>

class NetworkManager : public QObject {
	Q_OBJECT

public:
	static NetworkManager *getInstance();
	NetworkManager();
	virtual ~NetworkManager();

	void get(QString urlString, QVariantMap urlParams);
signals:
	void networkResponse(QString response);
	void networkResponseFailed(int error);
	void networkStatusChanged(bool activeConnection);
public slots:
	void onNetworkStateChanged(QNetworkSession::State state);
	void onNetworkRequestFinished(QNetworkReply* reply);


private:
	QNetworkConfigurationManager *_networkConfigManager;
	QNetworkSession *_networkSession;
	QNetworkAccessManager* _networkAccessManager;

};

#endif /* NETWORKMANAGER_HPP_ */
