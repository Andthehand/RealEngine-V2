#pragma once

#include <array>

namespace RealEngine {
    template <unsigned int size, typename T>
    class RingBuffer {
    public:
        RingBuffer() = default;

        void Push(const T& item) {
            m_Buffer[m_CurrentIndex] = item;
            m_CurrentIndex = (m_CurrentIndex + 1) % size;
            if (m_Count < size) ++m_Count;
        }

        void Clear() {
            m_CurrentIndex = 0;
            m_Count = 0;
		}

        static constexpr unsigned int Size() { return size; }
		unsigned int Count() const { return m_Count; }
        bool Full() const { return m_Count == size; }
		bool Empty() const { return m_Count == 0; }
    private:
        // ---- Iterators (logical order oldest->newest) ----
        template <bool IsConst>
        class basic_iterator {
        public:
            using ring_type = std::conditional_t<IsConst, RingBuffer const, RingBuffer>;
            using value_type = T;
            using reference = std::conditional_t<IsConst, T const&, T&>;
            using pointer = std::conditional_t<IsConst, T const*, T*>;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::random_access_iterator_tag;

            basic_iterator() noexcept : _buf(nullptr), _pos(0), _remaining(0) {}
            basic_iterator(ring_type* buf, unsigned int pos, unsigned int remaining) noexcept
                : _buf(buf), _pos(pos), _remaining(remaining) {
            }

            reference operator*() const noexcept { return _buf->m_Buffer[_pos]; }
            pointer operator->() const noexcept { return &(_buf->m_Buffer[_pos]); }

            // prefix increment
            basic_iterator& operator++() noexcept {
                if (_remaining > 0) {
                    _pos = (_pos + 1) % size;
                    --_remaining;
                }
                return *this;
            }

            // prefix decrement
            basic_iterator& operator--() noexcept {
                ++_remaining;
                _pos = (_pos + size - 1) % size;
                return *this;
            }

            // random access offset
            basic_iterator& operator+=(difference_type n) noexcept {
                if (n >= 0) {
                    auto adv = static_cast<unsigned int>(n);
                    if (adv > _remaining) adv = _remaining;
                    _pos = (_pos + adv) % size;
                    _remaining -= adv;
                }
                else {
                    auto back = static_cast<unsigned int>(-n);
                    _pos = (_pos + size - back % size) % size;
                    _remaining += back;
                }
                return *this;
            }

            basic_iterator operator+(difference_type n) const noexcept {
                basic_iterator tmp = *this;
                tmp += n;
                return tmp;
            }

            basic_iterator& operator-=(difference_type n) noexcept {
                return *this += -n;
            }

            basic_iterator operator-(difference_type n) const noexcept {
                basic_iterator tmp = *this;
                tmp -= n;
                return tmp;
            }

            difference_type operator-(basic_iterator const& other) const noexcept {
                // distance in logical order (approximate, valid for same buffer)
                return static_cast<difference_type>(other._remaining) -
                    static_cast<difference_type>(_remaining);
            }

            bool operator==(basic_iterator const& other) const noexcept {
                return _buf == other._buf && _remaining == other._remaining;
            }
            bool operator!=(basic_iterator const& other) const noexcept { return !(*this == other); }

            // relational comparisons for standard compatibility
            bool operator<(basic_iterator const& other) const noexcept {
                return _remaining > other._remaining;
            }
            bool operator>(basic_iterator const& other) const noexcept {
                return _remaining < other._remaining;
            }
            bool operator<=(basic_iterator const& other) const noexcept {
                return _remaining >= other._remaining;
            }
            bool operator>=(basic_iterator const& other) const noexcept {
                return _remaining <= other._remaining;
            }

        private:
            ring_type* _buf;
            unsigned int _pos;
            unsigned int _remaining;
        };
    public:
        using iterator = basic_iterator<false>;
        using const_iterator = basic_iterator<true>;

        // logical begin/end for mutable iteration
        iterator logical_begin() {
            unsigned int start = (m_CurrentIndex + size - m_Count) % size;
            return iterator(this, start, m_Count);
        }
        iterator logical_end() {
            return iterator(this, 0, 0);
        }

        // logical begin/end for const iteration
        const_iterator logical_begin() const {
            unsigned int start = (m_CurrentIndex + size - m_Count) % size;
            return const_iterator(this, start, m_Count);
        }
        const_iterator logical_end() const {
            return const_iterator(this, 0, 0);
        }

        // standard compatibility names
        iterator begin() { return logical_begin(); }
        iterator end() { return logical_end(); }
        const_iterator begin() const { return logical_begin(); }
        const_iterator end() const { return logical_end(); }
        const_iterator cbegin() const { return logical_begin(); }
        const_iterator cend() const { return logical_end(); }

    private:
        std::array<T, size> m_Buffer{};
        unsigned int m_CurrentIndex = 0;
        unsigned int m_Count = 0;
    };
}