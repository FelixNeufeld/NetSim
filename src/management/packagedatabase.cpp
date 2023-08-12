#include "packagedatabase.h"

using namespace NetSim;

PackageDatabase::PackageDatabase() {}

QList<Package> *PackageDatabase::packageList() { return &m_packageList; }

PackageDatabase *PackageDatabase::instance() {
  static PackageDatabase *model = new PackageDatabase();
  return model;
}
