/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_INTERFACES_IFRAGMENT_HPP_
#define _SDK_INTERFACES_IFRAGMENT_HPP_

#include <optional>
#include <string>
#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>
#include "sdk/structures/bidimensional.hpp"
#include "sdk/interfaces/Itheme.hpp"

class Ifragment {
    std::optional<std::string> &intent_ref;
protected:
    bidimensional::Transform &parent_transform;
    std::vector<std::pair<std::string, Ifragment *>> fragments;
public:
    sf::RectangleShape background;
private:
    void compute_content();
protected:
    sf::RenderWindow &window;
    /**
     * Must be set in fragment Ctor
     */
    bidimensional::Transform transform;

    /**
     * Must be set in the fragment ctor
     */
    sf::Color background_color = sf::Color::White;
    sf::View content;
    /**
     * this function is run at the fragment creation
     */
    virtual void onCreateView() = 0;
    /**
     * this function is call at each tick
     */
    virtual void onUpdateView() = 0;
    /**
    * this function is run at the fragment deletion
    */
    virtual void onFinishView() = 0;
    /**
     * To change to another view
     * @param view is the target view
     */
    void set_intent(const std::string &view);
    /**
     * Must be use only in a fragment Ctor
     * @tparam T T => fragment is a sub part of the View
     * @param key name
     */
    template<typename T>
    void add_fragment(const std::string &key) {
        static_assert(std::is_base_of<Ifragment, T>::value, "T doesn't derive from Ifragment");
        auto fragment = new T(intent_ref, transform, window);
        fragments.emplace_back(key, fragment);
    }
    /**
     * Must be use only in a fragment Ctor
     * @tparam T => fragment is a sub part of the View
     * @param key name
     * @param theme use reinterpret_cast<Itheme<Icolors *> *>(std::make_unique<Theme>().get())
     */
    template<typename T>
    void add_widget(const std::string &key, Itheme<Icolors *> *theme) {
        static_assert(std::is_base_of<Ifragment, T>::value, "T doesn't derive from Ifragment");
        auto fragment = new T(intent_ref, transform, window, theme);
        fragments.emplace_back(key, fragment);
    }
    /**
     * Get a fragment from the local list
     * @param key unique name of the fragment
     * @return founded fragment or nullptr
     */
    [[nodiscard]] Ifragment *get_fragment(const std::string &key);
    /**
     * Same as get_fragment() but return direct the specified type
     * @tparam T fragment type
     * @param key unique name of the fragment
     * @return founded fragment or nullptr
     */
    template<typename T>
    [[nodiscard]] T *get_fragment(const std::string &key) {
        Ifragment *ret = get_fragment(key);
        return reinterpret_cast<T *>(ret);
    }
public:
    /**
     * Must be set in the fragment ctor
     */
    unsigned z_index = 0;
    /**
     * All sub-fragments of the inherited class must be set in their Ctor
     * @param view_intent reference to the view intent
     * @param parent_trans transform of the parent fragment
     * @param main_window the main sf::RenderWindow
     */
    Ifragment(std::optional<std::string> &view_intent, bidimensional::Transform &parent_trans, sf::RenderWindow &main_window);
    virtual ~Ifragment();
    virtual void runCreate();
    virtual void runUpdate();
    virtual void runFinish();
    /**
     * Move fragment to a new position
     * @param pos
     */
    virtual void move(sf::Vector2<float> pos);
    /**
     * Scale fragment to a new scale
     * @param scale
     */
    virtual void scale(sf::Vector2<float> scale);
    void setViewCenter(sf::Vector2<float> coords);
    [[nodiscard]] sf::Vector2<float> getViewCenter() const;
private:
    void reload();
};

#endif