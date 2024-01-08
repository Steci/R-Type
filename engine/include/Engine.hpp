/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Engine.hpp
*/

#pragma once

#include <cassert>
#include <memory>

#include "Entity.hpp"

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
         * @param element The element to be added.
         * @param id The optional ID of the element.
         */
        int add(std::shared_ptr<T> element, int id = -1) {
            if (id == -1) {
                // Find the first available ID after the first 5
                for (int i = 5; i < sparse.size(); i++) {
                    if (sparse[i] == -1) {
                        id = i;
                        break;
                    }
                }
                if (id == -1) {
                    id = sparse.size();
                }
            }
            if (id >= sparse.size()) {
                sparse.resize(id + 1, -1);
            }
            if (sparse[id] == -1) {
                sparse[id] = dense.size();
                dense.push_back(std::move(element));
                indices.push_back(id);
            } else {
                // Replace if already exists
                dense[sparse[id]] = std::move(element);
            }
            return id;
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
            return *(dense[sparse[id]].get());
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

        /**
         * @brief Clears the array of all elements.
         *
         */
        void clearEntities() {
            dense.clear();
            sparse.clear();
            indices.clear();
        }

        /**
         * @brief Gets the all the elements in the dense array.
         *
         * @return The arrary of actual elements
         */
        std::vector<std::shared_ptr<T>>& getAll() {
            return dense;
        }

        /**
         * @brief Gets the all the elements in the dense array.
         *
         * @return The arrary of indexes
         */
        const std::vector<int>& getSparse() const {
            return sparse;
        }

        /**
         * @brief Gets the all the elements in the dense array.
         *
         * @return The arrary of indices
         */
        const std::vector<int>& getAllIndices() const {
            return indices;
        }

        std::vector<char> serializeToVector(const std::string& entityType) {
            std::vector<char> data;

            for (auto& element : dense) {
                if (element->getType() == entityType) {
                    std::string typeHeader = entityType;
                    data.insert(data.end(), typeHeader.begin(), typeHeader.end());
                    data.push_back('\0');
                    auto elementData = element->serializeToVector();
                    data.insert(data.end(), elementData.begin(), elementData.end());
                }
            }
            return data;
        }

    private:
        std::vector<std::shared_ptr<T>> dense; // Stores actual elements
        std::vector<int> sparse; // Maps IDs to indices in 'dense'
        std::vector<int> indices; // Stores original IDs
};
