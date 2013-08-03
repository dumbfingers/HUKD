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
	void onNetworkResponse(QUrl url, QString response);
	void onNetworkResponseFailed(QUrl url, int error);

private:
	void parseDealUpdateResponse(QString response);

};

#endif /* DEALRETRIEVER_HPP_ */
