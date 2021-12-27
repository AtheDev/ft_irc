#ifndef MESSAGE_HPP
# define MESSAGE_HPP

#include <sys/types.h>
#include <unistd.h>
#include <cstring>

#define BUF_SIZE 500

class Message
{
    public:
        //constructor
        Message();
        //destructor
        ~Message();

        void    setNread(ssize_t nread);
        ssize_t getNread(void) const;

        //char *  getBuf(void) const;

        char        _buf[BUF_SIZE];

    private:

        ssize_t     _nread;
        //char        _buf[BUF_SIZE];

};

#endif