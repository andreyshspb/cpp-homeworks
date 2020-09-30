#pragma once

#include <utility>
#include <vector>
#include <iterator>


namespace linq {

    namespace impl {

        template<typename T, typename Iter>
        class range_enumerator;
        template<typename T>
        class drop_enumerator;
        template<typename T, typename U, typename F>
        class select_enumerator;
        template<typename T, typename F>
        class until_enumerator;
        template<typename T>
        class take_enumerator;
        template<typename T, typename F>
        class where_enumerator;


        template<typename T>
        class enumerator {
        public:
            virtual const T &operator*() const = 0;
            virtual enumerator<T> &operator++() = 0;
            virtual explicit operator bool() const = 0;

            auto drop(int count) {
                return drop_enumerator<T>(*this, count);
            }

            template<typename U = T, typename F>
            auto select(F func) {
                return select_enumerator<U, T, F>(*this, func);
            }

            template<typename F>
            auto until(F func) {
                return until_enumerator<T, F>(*this, func);
            }

            auto until_eq(const T &val) {
                return until([&val](const T &elem) { return elem == val; });
            }

            auto take(int count) {
                return take_enumerator<T>(*this, count);
            }

            template<typename F>
            auto where(F func) {
                return where_enumerator<T, F>(*this, func);
            }

            auto where_neq(const T &val) {
                return where([&val](T elem) { return elem != val; });
            }

            std::vector<T> to_vector() {
                std::vector<T> result;
                this->copy_to(std::back_inserter(result));
                return result;
            }

            template<typename Iter>
            void copy_to(Iter it) {
                while (*this) {
                    *it = *(*this);
                    ++(*this);
                    ++it;
                }
            }
        };


        template<typename T, typename Iter>
        class range_enumerator : public enumerator<T> {
        public:
            range_enumerator<T, Iter>(Iter begin, Iter end) : begin_(begin), end_(end) {}

            const T &operator*() const override {
                return *begin_;
            }

            range_enumerator<T, Iter> &operator++() override {
                ++begin_;
                return *this;
            }

            explicit operator bool() const override {
                return begin_ != end_;
            }
        private:
            Iter begin_, end_;
        };


        template<typename T>
        class drop_enumerator : public enumerator<T> {
        public:
            drop_enumerator<T>(enumerator<T> &parent, int count) : parent_(parent) {
                while (*this && count > 0) {
                    ++parent_;
                    count--;
                }
            }
            drop_enumerator<T> &operator++() override {
                ++parent_;
                return *this;
            }

            const T &operator*() const override {
                return *parent_;
            }

            explicit operator bool() const override {
                return (bool)parent_;
            }

        private:
            enumerator<T> &parent_;

        };


        template<typename T, typename U, typename F>
        class select_enumerator : public enumerator<T> {
        public:
            select_enumerator<T, U, F>(enumerator<U> &parent, F func) : parent_(parent), func_(std::move(func)) {
                if (parent) {
                    current_ = func(*parent);
                }
            }

            select_enumerator<T, U, F> &operator++() override {
                if (++parent_) {
                    current_ = func_(*parent_);
                }
                return *this;
            }

            const T &operator*() const override {
                return current_;
            }

            explicit operator bool() const override {
                return (bool)parent_;
            }

        private:
            enumerator<U>& parent_;
            F func_;
            T current_;

        };


        template<typename T, typename F>
        class until_enumerator : public enumerator<T> {
        public:
            until_enumerator<T, F>(enumerator<T> &parent, F func) : parent_(parent), func_(std::move(func)) {
                if (func_(*(*this))) {
                    stop_ = true;
                }
            }

            until_enumerator<T, F> &operator++() override {
                ++parent_;
                if (*this && func_(*(*this))) {
                    stop_ = true;
                }
                return *this;
            }

            const T &operator*() const override {
                return *parent_;
            }

            explicit operator bool() const override {
                return !stop_ && (bool)parent_;
            }

        private:
            bool stop_ = false;
            enumerator<T> &parent_;
            F func_;

        };


        template<typename T>
        class take_enumerator : public enumerator<T> {
        public:
            take_enumerator<T>(enumerator<T> &parent, int count) : parent_(parent), count_(count) {}

            take_enumerator<T> &operator++() override {
                ++parent_;
                count_--;
                return *this;
            }

            const T &operator*() const override {
                return *parent_;
            }

            explicit operator bool() const override {
                return (bool)parent_ && count_ > 0;
            }

        private:
            enumerator<T> &parent_;
            int count_;

        };


        template<typename T, typename F>
        class where_enumerator : public enumerator<T> {
        public:
            where_enumerator<T, F>(enumerator<T> &parent, F func) : parent_(parent), func_(std::move(func)) {
                while (*this && !func_(*parent_)) {
                    ++parent_;
                }
            }

            where_enumerator<T, F> &operator++() override {
                ++parent_;
                while (*this && !func_(*(*this))) {
                    ++parent_;
                }
                return *this;
            }

            const T &operator*() const override {
                return *parent_;
            }

            explicit operator bool() const override {
                return (bool)parent_;
            }

        private:
            enumerator<T> &parent_;
            F func_;

        };

    } // namespace impl


    template<typename Iter>
    auto from(Iter begin, Iter end) {
        return impl::range_enumerator<typename std::iterator_traits<Iter>::value_type, Iter>(begin, end);
    }

} // namespace linq
