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
	connect(NetworkManager::getInstance(), SIGNAL(networkResponse(QString)), this, SLOT(onNetworkResponse(QString)));
	connect(NetworkManager::getInstance(), SIGNAL(networkResponseFailed(int)), this, SLOT(onNetworkResponseFailed(int)));
}

DealRetriever::~DealRetriever() {
	// TODO Auto-generated destructor stub
}

void DealRetriever::fetchDeals(QString apiKey) {
	QVariantMap urlParams;
	urlParams["key"] = apiKey;
	NetworkManager::getInstance()->get("http://api.hotukdeals.com/rest_api/v2/", urlParams);
}

void DealRetriever::onNetworkResponse(QString response) {
	this->parseDealUpdateResponse(response);
}

void DealRetriever::onNetworkResponseFailed(int error) {
	qDebug() << "onNetworkResponseFailed: " << error;
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

	QVariantMap dealsObj = dealResponse["deals"].toMap();
	QVariantList dealsList = dealsObj["items"].toList();
	foreach(QVariant item, dealsList) {
		QVariantMap deal = item.toMap();
		QString title = deal["title"].toString();
		qDebug() << "Loading Deal Title: " << title;
	}
}
