#include "Headernotfoundexception.h"

HeaderNotFoundException::HeaderNotFoundException(const QString &errorMessage) {
  this->m_errorMessage = errorMessage;
}

QString HeaderNotFoundException::errorMessage() const {
  return this->m_errorMessage;
}
