#include "GameDownload.h"

#include "assistance/PathReplacer.h"
#include "exception/Exceptions.hpp"

#include <QFile>
#include <QJsonDocument>

GameDownload::GameDownload(QObject *parent) :
	QObject(parent),
	manifestFile_(PathReplacer::replace("<launcher>/version_manifest.json"))
{
	proxyModel_.setSourceModel(&model_);
	proxyModel_.setFilterKeyColumn(Column::Type);

	model_.setColumnCount(5);
	model_.setHeaderData(Column::Id, Qt::Horizontal, tr("Version Id"));
	model_.setHeaderData(Column::Type, Qt::Horizontal, tr("Type"));
	model_.setHeaderData(Column::Time, Qt::Horizontal, tr("Time"));
	model_.setHeaderData(Column::ReleaseTime, Qt::Horizontal, tr("Release Time"));
	model_.setHeaderData(Column::Url, Qt::Horizontal, tr("Url"));
}

QAbstractItemModel *GameDownload::getModel()
{
	return &proxyModel_;
}

void GameDownload::loadVersions()
{
	for(const auto &i: manifestObject_.value("versions").toVariant().toList())
		model_.appendRow(QList<QStandardItem*>{
							 new QStandardItem(i.toMap().value("id").toString()),
							 new QStandardItem(i.toMap().value("type").toString()),
							 new QStandardItem(i.toMap().value("time").toString()),
							 new QStandardItem(i.toMap().value("releaseTime").toString()),
							 new QStandardItem(i.toMap().value("url").toString())
						 });
}

GameVersion GameDownload::getGameVersion(const QString &versionName) const
{
	return versionsMap_.value(versionName);
}

void GameDownload::reapplyFilter(bool enableSnapshot, bool enableOldBeta, bool enableOldAlpha)
{
	QString str = "(release)";
	if(enableSnapshot)
		str.append("|(snapshot)");
	if(enableOldBeta)
		str.append("|(old_beta)");
	if(enableOldAlpha)
		str.append("|(old_alpha)");
	proxyModel_.setFilterRegExp(QRegExp(str));
}

void GameDownload::loadManifest()
{
	if(!manifestFile_.open(QIODevice::ReadOnly))
		throw FileOpenException(manifestFile_.fileName());

	QByteArray jsonByte;
	jsonByte.resize(static_cast<int>(manifestFile_.bytesAvailable()));
	jsonByte = manifestFile_.readAll();
	manifestFile_.close();

	QJsonParseError ok;
	manifestObject_ = QJsonDocument::fromJson(jsonByte,&ok).object();
	if(ok.error != QJsonParseError::NoError)
		throw JsonParseException(manifestFile_.fileName(), ok.errorString(), true);

	for(const auto &i: manifestObject_.value("versions").toVariant().toList()){
		versionsMap_.insert(i.toMap().value("id").toString(),
							GameVersion(i.toMap().value("id").toString(),
										i.toMap().value("url").toString()));
	}
	loadVersions();
}
