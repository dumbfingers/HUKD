/*
 * DealRetriever.hpp
 *
 *  Created on: Aug 3, 2013
 *      Author: Yaxi Ye
 */

#ifndef DEALRETRIEVER_HPP_
#define DEALRETRIEVER_HPP_

#include<QObject>
#include<QUrl>
#include<QVariant>

class DealRetriever : public QObject {
	Q_OBJECT

public:
	DealRetriever(QObject* parent = 0);
	virtual ~DealRetriever();

signals:
	void dealUpdated(QVariantMap dealInfo);
	void dealUpdateFailed();
private slots:
	void onNetworkResponse(QString response);
	void onNetworkResponseFailed(int error);

private:
	void parseDealUpdateResponse(QString response);
	void fetchDeals(QString apiKey);
};

#endif /* DEALRETRIEVER_HPP_ */
