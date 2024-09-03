//
// Created by Flash on 9/11/2023.
//

#pragma once

#include <string_view>
#include <span>


struct Resource {
    Resource(const char* begin, const char* end) : _begin(begin), _end(end) {}
    [[nodiscard]] const char* data() const { return _begin; }
    [[nodiscard]] void* data2() const { return (void*)_begin; }
    [[nodiscard]] const char* begin() const { return _begin; }
    [[nodiscard]] const char* end() const { return _end; }
    [[nodiscard]] size_t size() const { return size_t(_end - _begin); }
    [[nodiscard]] std::string_view str() const { return std::string_view{this->data(), this->size()}; }
    [[nodiscard]] std::span<const std::byte> bytes() const {
        return {
                reinterpret_cast<const std::byte*>(this->begin()),
                reinterpret_cast<const std::byte*>(this->end())
        };
    }
private:
    const char* _begin;
    const char* _end;
};

#define LOAD_RESOURCE(x) extern "C" char _binary_resources_##x##_start, _binary_resources_##x##_end;

#define GET_RESOURCE(x) Resource{&_binary_resources_##x##_start, &_binary_resources_##x##_end}