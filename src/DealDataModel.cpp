/*
 * DealDataModel.cpp
 *
 *  Created on: Aug 3, 2013
 *      Author: Yaxi Ye
 */

#include "DealDataModel.hpp"

using namespace bb::cascades;

DealDataModel::DealDataModel(QObject *parent) : DataModel(parent) {
	// TODO Auto-generated constructor stub

}

DealDataModel::~DealDataModel() {
	// TODO Auto-generated destructor stub
}

//QVariant DealDataModel::data(const QVariantList &indexPath) {
//	if (indexPath.length() == 1) {
////		QVariantMap map = indexPath.value(0).toInt(NULL)
//	} else if (indexPath.length() == 2) {
//
//	} else if (indexPath.length() == 3) {
//
//	}
//}

void DealDataModel::onDealUpdated() {

}
void DealDataModel::onDealUpdateError() {

}
