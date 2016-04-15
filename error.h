#ifndef __ERROR_H__
#define __ERROR_H__

#include"base.h"

typedef int uv_err_t;

namespace native
{
    class exception
    {
    public:
        exception(const std::string& message)
            : message_(message)
        {}

        virtual ~exception() {}

        const std::string& message() const { return message_; }

    private:
        std::string message_;
    };

    class error
    {
    public:
        error() : uv_err_() {}
        error(uv_err_t e) : uv_err_(e) {}
		int getError() { return uv_err_; }
        ~error() = default;

    public:
        const char* name() const { return uv_err_name(uv_err_); }
        const char* str() const { return uv_strerror(uv_err_); }

    private:
        uv_err_t uv_err_;
    };

    error get_last_error() { return errno; }
}


#endif
