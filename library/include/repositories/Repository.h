#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "typedefs.h"
#include "string"
#include "vector"
#include "Package.h"
#include <algorithm>
#include <iostream>


template<class T>
class Repository {
private:
    std::vector<T> collection;

public:
    /**
     * @brief Retrieves an entity by its identifier.
     *
     * @param id The identifier of the entity.
     * @return The entity with the specified identifier, or nullptr if not found.
     */
    T get(const std::string &id) const;

    /**
     * @brief Adds a new entity to the repository.
     *
     * @param entity The entity to be added.
     * @return True if the entity was added successfully, false if it already exists or is null.
     */
    bool add(const T& entity);

    /**
     * @brief Removes an entity from the repository.
     *
     * @param entity The entity to be removed.
     * @return True if the entity was removed successfully, false if it was not found or is null.
     */
    bool remove(const T& entity);


    /**
     * @brief Generates a report of all entities in the repository.
     *
     * @return A string representation of all entities in the repository.
     */
    std::string report() const;

    /**
     * @brief Gets the number of entities in the repository.
     *
     * @return The number of entities.
     */
    int size() const;

    /**
    * @brief Finds entities based on a predicate.
    *
    * @param predicate A function that determines whether an entity matches the criteria.
    * @return A vector of entities that match the predicate.
    */
    std::vector<T> findBy(Predicate<T> predicate) const;

    /**
     * @brief Applies a function to each entity in the repository.
     *
     * @param predicate A function to be applied to each entity.
     */
    void foreach(PredicateVoid<T> predicate) const;

    /**
     * @brief Finds one entity based on a predicate.
     *
     * @param predicate A function that determines whether an entity matches the criteria.
     * @return The first entity that matches the predicate, or nullptr if none found.
     */
    T findOneBy(Predicate<T> predicate) const;

    /**
     * @brief Retrieves all entities in the repository.
     *
     * @return A vector of all entities.
     */
    std::vector<T> findAll() const;

    Repository();

    ~Repository();
};





template<class T>
T Repository<T>::get(const std::string &id) const {
    for (T entity : collection)
        if (entity->get_id() == id) return entity;
    return nullptr;
}

template<class T>
bool Repository<T>::add(const T &entity) {
    if (entity == nullptr) return false;
    for (auto element: collection)
        if (element == entity) return false;
    collection.emplace_back(entity);
    return true;

}

template<class T>
bool Repository<T>::remove(const T &entity) {
    if (entity == nullptr) return false;
    if (get(entity->get_id()) != entity) return false;
    collection.erase(
            std::remove_if(
                    collection.begin(),
                    collection.end(),
                    [entity](const T& _entity) { return _entity == entity; }
            ), collection.end()
    );
    return true;
}

template<class T>
std::string Repository<T>::report() const {
    std::string result;
    for (const auto& entry: collection)
        result += entry->get_info() + "\n";
    return result;
}

template<class T>
int Repository<T>::size() const {
    return (int)collection.size();
}

template<class T>
std::vector<T> Repository<T>::findBy(Predicate<T> predicate) const {
    std::vector<T> found;
    for (const T& entity : collection)
        if (predicate(entity)) found.emplace_back(entity);
    return found;
}

template<class T>
void Repository<T>::foreach(PredicateVoid<T> predicate) const {
    for (const T& entity : collection)
        predicate(entity);
}

template<class T>
T Repository<T>::findOneBy(Predicate<T> predicate) const {
    for (const T& entity : collection)
        if (predicate(entity)) return entity;
    return nullptr;
}

template<class T>
std::vector<T> Repository<T>::findAll() const {
    return findBy([](const T&) { return true;});
}

template<class T>
Repository<T>::Repository() {
}

template<class T>
Repository<T>::~Repository() {
}

#endif