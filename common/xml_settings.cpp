
#include "xml_settings.h"
#include "string_helper.h"
#include <pugixml.hpp>

XmlSettings::XmlSettings() {
    mRoot = std::make_unique<pugi::xml_node>();
    mCurrBase = std::make_unique<pugi::xml_node>();
}

XmlSettings::~XmlSettings() {}

bool XmlSettings::Load(std::string filename) {
    *mRoot = {};
    *mCurrBase = {};

    mDocument = std::make_unique<pugi::xml_document>();
    if (!mDocument->load_file(filename.c_str())) return false;

    return true;
}

bool XmlSettings::setBase(std::string xpath) {
    try {
        auto xpathNode = mDocument->select_nodes(xpath.c_str());
        *mRoot = xpathNode.first().node();
        *mCurrBase = *mRoot;

        return true;
    } catch (pugi::xpath_exception &e) {
        return false;
    }
}

void XmlSettings::assignValueF(float *buf, std::string key) {
    auto node = mCurrBase->child(key.c_str());
    if(node)
        *buf = node.text().as_float();
}
void XmlSettings::assignValueD(double *buf, std::string key) {
    auto node = mCurrBase->child(key.c_str());
    if (node) *buf = node.text().as_double();
}
void XmlSettings::assignValueV3(Vector3DF *buf, std::string key) {
    auto node = mCurrBase->child(key.c_str());
    if (node) *buf = ParseVector3(node.text().as_string());
}
void XmlSettings::assignValueStr(std::string &str, std::string key) {
    auto node = mCurrBase->child(key.c_str());
    if (node) str = node.text().as_string();
}

Vector3DF XmlSettings::ParseVector3(std::string vec) {
    std::vector<std::string> vals = StringHelper::SplitString(vec, ',');
    float x = atof(vals[0].c_str());
    float y = atof(vals[1].c_str());
    float z = atof(vals[2].c_str());
    return Vector3DF(x, y, z);
}

Vector4DF XmlSettings::ParseVector4(std::string vec) {
    if (vec.length() == 0) return Vector4DF();
    str_vec_t vals = StringHelper::SplitString(vec, ',');

    float x = atof(vals[0].c_str());
    float y = atof(vals[1].c_str());
    float z = atof(vals[2].c_str());
    float w = atof(vals[3].c_str());
    return Vector4DF(x, y, z, w);
}