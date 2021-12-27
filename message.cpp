#include "message.hpp"

Message::Message() {

    memset(_buf, 0, BUF_SIZE);
}

Message::~Message() {}

void    Message::setNread(ssize_t nread) {

    _nread = nread;
}

ssize_t Message::getNread(void) const {

    return _nread;
}

/*char *  Message::getBuf(void) const {

    return _buf;
}*/