/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Engine.hpp
*/

#pragma once

#include <vector>
#include <cassert>

#include "Entity.hpp"
#include "Component.hpp"
#include "System.hpp"

/**
 * @brief A sparse array data structure that maps IDs to elements.
 *
 * The SparseArray class provides a way to store elements with associated IDs
 * in a sparse array. It allows adding, removing, and accessing elements based
 * on their IDs. The class ensures efficient memory usage by using a sparse
 * array representation.
 *
 * @tparam T The type of elements stored in the array.
 */
template<typename T>
class SparseArray {
    public:
        /**
         * @brief Adds an element to the array with the specified ID.
         *
         * If the ID is greater than or equal to the current size of the sparse
         * array, the array is resized to accommodate the new ID. If the ID
         * already exists in the array, the element at that ID is replaced with
         * the new element.
         *
         * @param id The ID of the element.
         * @param element The element to be added.
         */
        void add(int id, const T& element) {
            if (id >= sparse.size()) {
                sparse.resize(id + 1, -1);
            }

            if (sparse[id] == -1) {
                sparse[id] = dense.size();
                dense.push_back(element);
                indices.push_back(id);
            } else {
                // Replace if already exists
                dense[sparse[id]] = element;
            }
        }

        /**
         * @brief Removes the element with the specified ID from the array.
         *
         * The ID must be valid and exist in the array. The element is removed
         * from the array, and the array is updated accordingly.
         *
         * @param id The ID of the element to be removed.
         */
        void remove(int id) {
            assert(id < sparse.size() && sparse[id] != -1 && "Invalid ID");

            int denseIndex = sparse[id];
            int lastIndex = dense.size() - 1;
            int lastID = indices[lastIndex];

            std::swap(dense[denseIndex], dense[lastIndex]);
            std::swap(indices[denseIndex], indices[lastIndex]);

            sparse[lastID] = denseIndex;
            sparse[id] = -1;

            dense.pop_back();
            indices.pop_back();
        }

        /**
         * @brief Retrieves a reference to the element with the specified ID.
         *
         * The ID must be valid and exist in the array. A reference to the
         * element is returned, allowing modification of the element.
         *
         * @param id The ID of the element to be retrieved.
         * @return A reference to the element.
         */
        T& get(int id) {
            assert(id < sparse.size() && sparse[id] != -1 && "Invalid ID");
            return dense[sparse[id]];
        }

        /**
         * @brief Checks if an element with the specified ID exists in the array.
         *
         * @param id The ID to check.
         * @return True if an element with the ID exists, false otherwise.
         */
        bool exists(int id) const {
            return id < sparse.size() && sparse[id] != -1;
        }

    private:
        std::vector<T> dense; // Stores actual elements
        std::vector<int> sparse; // Maps IDs to indices in 'dense'
        std::vector<int> indices; // Stores original IDs
};

// Usage
// SparseArray<YourEntityType> entities;
// entities.add(entityId, entity);

// TODO : IMPLEMENT RESSOURCE MANAGER
