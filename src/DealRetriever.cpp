/*
 * DealRetriever.cpp
 *
 *  Created on: Aug 3, 2013
 *      Author: Yaxi Ye
 */

#include "DealRetriever.hpp"
#include "NetworkManager.hpp"
#include <bb/data/JsonDataAccess>

using namespace bb::data;


DealRetriever::DealRetriever(QObject* parent) : QObject(parent) {
	connect(NetworkManager::getInstance(), SIGNAL(networkResponse(QUrl, QString), this, SLOT(onNetworkResponse(QUrl, QString))));
	connect(NetworkManager::getInstance(), SIGNAL(networkResponseFailed(QUrl, int), this, SLOT(onNetworkResponseFailed(QUrl, int))));
}

DealRetriever::~DealRetriever() {
	// TODO Auto-generated destructor stub
}

void DealRetriever::onNetworkResponse(QUrl url, QString response) {
	this->parseDealUpdateResponse(response);
}

void DealRetriever::onNetworkResponseFailed(QUrl url, int error) {
	emit dealUpdateFailed();
}

void DealRetriever::parseDealUpdateResponse(QString response) {
	JsonDataAccess jda;
	QVariantMap dealResponse = jda.loadFromBuffer(response).toMap();

	if (jda.hasError()) {
		DataAccessError error = jda.error();
		qDebug() << "JSON loading error: " << error.errorType() << ": " << error.errorMessage();
		emit dealUpdateFailed();
		return;
	}


}
