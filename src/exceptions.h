/*
 * MIT License
 *
 * Copyright (c) 2016 Caetano Sauer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef FOSTER_BTREE_EXCEPTIONS_H
#define FOSTER_BTREE_EXCEPTIONS_H

/**
 * \file exceptions.h
 *
 * Definition of exceptions that can be thrown anywhere in the Foster B-tree code.
 */

#include <sstream>

namespace foster {

/**
 * \brief Base class for all Foster B-tree exceptions
 *
 * Maintain a stringstream object that allows derived classes to produce their own error messages
 * depending on their own fields. To build a customized message, derived classes simply override the
 * build_msg() method and write into the protected msg_ field.
 */
struct FosterBtreeException
{
    virtual const char* what()
    {
        build_msg();
        return msg_.str().c_str();
    }

protected
    std::stringstream msg_;

    virtual void build_msg()
    {}
};

/// Thrown when a key is found when it should not be there (e.g., inserting duplicates)
template <class K>
struct ExistentKeyException : protected FosterBtreeException
{
    ExistentKeyException(const K& key) : key_(key)
    {}

protected:
    K key_;

    virtual void build_msg()
    {
        msg_ << "Key already exists: " << key_;
    }
};

/// Thrown when a key which must be present is not found (e.g., deletion)
template <class K>
struct KeyNotFoundException : protected FosterBtreeException
{
    KeyNotFoundException(const K& key) : key_(key)
    {}

protected:
    K key_;

    virtual void build_msg()
    {
        msg_ << "Key not found: " << key_;
    }
};

} // namespace foster

#endif
