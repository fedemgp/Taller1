#include "stagedata.h"
#include <QDebug>
#include <cassert>

const qreal scale = 13.0;

YAML::Emitter& operator<<(YAML::Emitter& out, const QColor& v) {
    out << YAML::Flow;
    out << YAML::BeginSeq << v.red() << v.green() << v.blue() << YAML::EndSeq;
    return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const QPointF& v) {
    out << YAML::Flow;
    out << YAML::BeginSeq << v.x() << v.y() << YAML::EndSeq;
    return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const WormData& v) {
    out << YAML::BeginMap;

    out << YAML::Key << "position";
    out << YAML::Value << v.position;

    out << YAML::EndMap;
    return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const GirderData& v) {
    out << YAML::BeginMap;

    out << YAML::Key << "position";
    out << YAML::Value << v.position;

    out << YAML::Key << "angle";
    out << YAML::Value << v.angle;

    out << YAML::Key << "length";
    out << YAML::Value << v.length;

    out << YAML::EndMap;
    return out;
}

StageData::StageData(qreal width, qreal height) : width(width / scale), height(height / scale) {}

QPointF StageData::toGameCoords(const QPointF& point) const {
    qreal xpos = (point.x() / scale - this->width / 2.0);
    qreal ypos = this->height - point.y() / scale;
    return QPointF(xpos, ypos);
}

std::size_t StageData::numWorms() const {
    return this->worms.size();
}

void StageData::dump(std::ostream& output, std::string fileName) {
    YAML::Emitter emitter;

    emitter << YAML::BeginMap;

    emitter << YAML::Key << "name";
    emitter << YAML::Value << fileName;

    emitter << YAML::Key << "numPlayers";
    emitter << YAML::Value << this->numPlayers;

    emitter << YAML::Key << "weaponsAmmo";
    emitter << YAML::Value << this->weapons;

    emitter << YAML::Key << "width";
    emitter << YAML::Value << this->width;

    emitter << YAML::Key << "height";
    emitter << YAML::Value << this->height;

    emitter << YAML::Key << "wormsHealth";
    emitter << YAML::Value << this->wormsHealth;

    emitter << YAML::Key << "worms";
    emitter << YAML::Value << this->worms;

    emitter << YAML::Key << "girders";
    emitter << YAML::Value << this->girders;

    emitter << YAML::Key << "background";
    emitter << YAML::Value;
    {
        emitter << YAML::BeginMap;
        emitter << YAML::Key << "closeBackgroundFile";
        emitter << YAML::Value << this->closeBgFile.toStdString();

        emitter << YAML::Key << "midBackgroundFile";
        emitter << YAML::Value << this->medianBgFile.toStdString();

        emitter << YAML::Key << "fartherBackgroundFile";
        emitter << YAML::Value << this->fartherBgFile.toStdString();

        emitter << YAML::Key << "color";
        emitter << YAML::Value << this->bgColor;

        emitter << YAML::EndMap;
    }

    emitter << YAML::EndMap;

    assert(emitter.good());

    output << emitter.c_str();
}

void StageData::addWorm(QPointF position) {
    this->worms.push_back(WormData{this->toGameCoords(position)});
}

void StageData::addShortGirder(QPointF position, qreal angle) {
    this->girders.push_back(GirderData{this->toGameCoords(position), -angle, 5.3845});
}

void StageData::addLongGirder(QPointF position, qreal angle) {
    this->girders.push_back(GirderData{this->toGameCoords(position), -angle, 10.769});
}

void StageData::addWeaponAmmo(QString weaponName, int ammo) {
    this->weapons[weaponName.toStdString()] = ammo;
}
