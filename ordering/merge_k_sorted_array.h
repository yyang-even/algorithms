#pragma once


template <typename Iterator>
void MergeKSortedArrays(const std::vector<std::vector<int>> &k_arrays,
                        Iterator out_iter) {
    using Node = std::pair<const std::vector<int> *, std::vector<int>::const_iterator>;

    std::vector<Node> first_elements;
    for (const auto &a : k_arrays) {
        if (not a.empty()) {
            first_elements.emplace_back(&a, a.cbegin());
        }
    }

    constexpr auto compare = [](const auto & lhs, const auto & rhs) {
        return  *lhs.second > *rhs.second;
    };
    std::priority_queue<Node, std::vector<Node>, decltype(compare)> heap(compare,
            std::move(first_elements));

    while (not heap.empty()) {
        const auto [top_array_ptr, top_array_iter] = heap.top();
        heap.pop();
        *(out_iter++) = *top_array_iter;

        const auto next = std::next(top_array_iter);
        if (next != top_array_ptr->cend()) {
            heap.emplace(top_array_ptr, next);
        }
    }
}
