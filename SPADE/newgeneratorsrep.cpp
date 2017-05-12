#ifndef GENERATORSREP_H
#define GENERATORSREP_H
#include "def.h"

#include <msgpack.hpp>

#include <chrono>
#include <random>
#include <functional>
#include <map>

#include <cstdarg>

#define WANT4 1
#define WANT6 2

namespace dht {

using NetId = uint32_t;
using want_t = int_fast8_t;


class GeneratorsRep
{
public:
    GeneratorsRep();
};


// shortcut for std::shared_ptr
template<class T>
using Sp = std::shared_ptr<T>;

template <typename Key, typename Item, typename Condition>
void erase_if(std::map<Key, Item>& map, const Condition& condition)
{
    for (auto it = map.begin(); it != map.end(); ) {
        if (condition(*it)) {
            it = map.erase(it);
        } else { ++it; }
    }
}

class OPENDHT_PUBLIC DhtException : public std::runtime_error {
    public:
        DhtException(const std::string &str = "") :
            std::runtime_error("DhtException occurred: " + str) {}
};

// Time related definitions and utility functions

using clock = std::chrono::steady_clock;
using time_point = clock::time_point;
using duration = clock::duration;

time_point from_time_t(std::time_t t);
std::time_t to_time_t(time_point t);

/**
 * Converts std::chrono::duration to floating-point seconds.
 */
template <class DT>
static double
print_dt(DT d) {
    return std::chrono::duration_cast<std::chrono::duration<double>>(d).count();
}

template <typename Duration = duration>
class uniform_duration_distribution : public std::uniform_int_distribution<typename Duration::rep> {
    using Base = std::uniform_int_distribution<typename Duration::rep>;
    using param_type = typename Base::param_type;
public:
    uniform_duration_distribution(Duration min, Duration max) : Base(min.count(), max.count()) {}
    template <class Generator>
    Duration operator()(Generator && g) {
        return Duration(Base::operator()(g));
    }
    template< class Generator >
    Duration operator()( Generator && g, const param_type& params ) {
        return Duration(Base::operator()(g, params));
    }
};

// Serialization related definitions and utility functions

using Blob = std::vector<uint8_t>;

/**
 * Provides backward compatibility with msgpack 1.0
 */
OPENDHT_PUBLIC Blob unpackBlob(msgpack::object& o);

template <typename Type>
Blob
packMsg(const Type& t) {
    msgpack::sbuffer buffer;
    msgpack::packer<msgpack::sbuffer> pk(&buffer);
    pk.pack(t);
    return {buffer.data(), buffer.data()+buffer.size()};
}

template <typename Type>
Type
unpackMsg(Blob b) {
    msgpack::unpacked msg_res = msgpack::unpack((const char*)b.data(), b.size());
    return msg_res.get().as<Type>();
}

msgpack::unpacked unpackMsg(Blob b);

msgpack::object* findMapValue(msgpack::object& map, const std::string& key);

} // namespace dht




#endif // GENERATORSREP_H