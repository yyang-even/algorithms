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

    const auto compare = [](const Node & lhs, const Node & rhs) {
        return  *lhs.second > *rhs.second;
    };
    std::priority_queue<Node, std::vector<Node>, decltype(compare)> heap(compare,
            std::move(first_elements));

    while (not heap.empty()) {
        const auto elem = heap.top();
        heap.pop();
        *(out_iter++) = *elem.second;

        const auto next = std::next(elem.second);
        if (next != elem.first->cend()) {
            heap.emplace(elem.first, next);
        }
    }
}
