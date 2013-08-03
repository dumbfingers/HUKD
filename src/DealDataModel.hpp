/*
 * DealDataModel.hpp
 *
 *  Created on: Aug 3, 2013
 *      Author: Yaxi Ye
 */

#ifndef DEALDATAMODEL_HPP_
#define DEALDATAMODEL_HPP_

#include <QObject>
#include <bb/cascades/DataModel>
#include <bb/cascades/ArrayDataModel>

class DealDataModel {
public:
	DealDataModel();
	virtual ~DealDataModel();

//	Q_INVOKABLE virtual QString itemType(const QVariantList &indexPath);
	Q_INVOKABLE virtual QVariant data(const QVariantList &indexPath);

//	Q_INVOKABLE virtual void removeItems(const QVariantList &indexPath);
};

#endif /* DEALDATAMODEL_HPP_ */
