#ifndef CALGORITHM_H
#define CALGORITHM_H

#include "shepherd.h"
#include "agent.h"
#include "other_object.h"

#include <QList>


/*!
 * \brief Класс для объектов-преград
 * \author Карпова Е.А.
 * \version 1.0
 * \date Май 2017 года
 *
 * Данный класс отвечает за работу алгоритма пастушьей собаки
 */
class CAlgorithm
{
public:
    CAlgorithm();
    ~CAlgorithm();

    /*!
     * \brief Возвращает радиус цели
     * \return Радиус цели
     *
     */
    int get_goal_radius();

    /*!
     * \brief Запускает одну итерацию алгоритма
     */
    void execution();

    /*!
     * \brief Устанавливает тип пастуха
     * \param flag Тип пастуха
     *
     * Если flag равен True, то в алгоритме используется
     * виртуальный пастух, иначе - реальный
     */
    void set_virtual_shepherd(bool flag);

    /*!
     * \brief Устанавливает центр генерации агентов
     * \param gen_center Точка-центр генерации агентов
     */
    void set_gen_center(QPoint gen_center);

    /*!
     * \brief Устанавливает размер поля генерации агентов
     * \param size Точка содержит в себе длину и ширину поля генерации агентов
     */
    void set_gen_size(QPoint size);

    /*!
     * \brief Устанавливает количество агентов
     * \param quantity Количество агентов
     */
    void set_agent_quantity(int quantity);

    /*!
     * \brief Устанавливает координаты цели
     * \param goal Точка, содержащая в себе координаты цели
     */
    void set_goal(QPoint goal);

    /*!
     * \brief Устанавливает количество ближайших соседей для агента
     * \param quantity Количество соседей
     */
    void set_agent_nearest_quantity(int quantity);

    /*!
     * \brief Устанавливает радиус реакции агентов на других агентов
     * \param radius Радиус реакции на агентов
     */
    void set_agents_agent_reaction(int radius);

    /*!
     * \brief Устанавливает радиус реакции агентов на пастуха
     * \param radius Радиус реакции на пастуха
     */
    void set_agents_shepherd_reaction(int radius);

    /*!
     * \brief Устанавливает радиус реакции агентов на объекты-преграды
     * \param radius Радиус реакции на преграды
     */
    void set_agents_other_reaction(int radius);

    /*!
     * \brief Устанавливает силу отталкивания агентов друг от друга
     * \param strength Сила отталкивания
     */
    void set_agents_agent_repulsion(double strength);

    /*!
     * \brief Устанавливает силу притяжения агентов друг к другу
     * \param strength Сила притяжения
     */
    void set_agents_agent_attraction(double strength);

    /*!
     * \brief Устанавливает силу отталкивания агентов от пастуха
     * \param strength Сила отталкивания
     */
    void set_agents_shepherd_repulsion(double strength);

    /*!
     * \brief Устанавливает силу отталкивания агентов от объектов-преград
     * \param strength Сила отталкивания
     */
    void set_agents_other_repulsion(double strength);

    /*!
     * \brief Устанавливает коэффициент инерции для агентов
     * \param inertia Инерция
     *
     * Устанавливаемый коэффициент влияет на направление агента по инерции
     */
    void set_agents_inertia(double inertia);

    /*!
     * \brief Учтанавливает коэффициент шума для направления агентов
     * \param noise Шум
     */
    void set_agents_noise(double noise);

    /*!
     * \brief Устанавливает вероятность случайных передвижений агентов
     * \param probability Вероятность
     */
    void set_agents_movement_probability(double probability);

    /*!
     * \brief Устанавливает скорость передвижения агентов
     * \param speed Скорость
     */
    void set_agent_speed(double speed);

    /*!
     * \brief Устанавливает скорость предвижения пастуха
     * \param speed Скорость
     */
    void set_shepherd_speed(double speed);

    /*!
     * \brief Устанавливает коэффициент шума для направления пастуха
     * \param noise Шум
     */
    void set_shepherd_noise(double noise);

    /*!
     * \brief Добавляет новый объект
     * \param name Имя объекта
     * \param position Позиция объекта
     * \param radius Радиус объекта
     */
    void add_object(QString name, QPoint position, int radius);

    /*!
     * \brief Меняет параметры имеющегося объекта
     * \param index Номер объекта
     * \param name Новое имя объекта
     * \param position Новая позиция объекта
     * \param radius Новый радиус объекта
     */
    void change_object(int index, QString name, QPoint position, int radius);

    /*!
     * \brief Удаляет имеющийся на поле объекта
     * \param index Номер объекта
     */
    void delete_object(int index);

    /*!
     * \brief Удаляет все имеющиеся на поле объекты-преграды
     */
    void clear_objects();

    /*!
     * \brief Генерирует агентов в пределах заданного ранее поля генерации
     * \return Статус при завершении генерации
     *
     * Если генерация была выполнена успешно, то возвращается True, иначе - False
     */
    bool gen_agents();

    /*!
     * \brief Генерация пастуха
     * \param position Начальная позиция пастуха
     * \return Статус при завершении генерации
     *
     * Если генерация была выполнена успешно, то возвращается True, иначе - False
     */
    bool gen_shepherd(QPoint position);

    /*!
     * \brief Проверяет положение группы относительно цели
     * \return Результат проверки
     *
     * Если группа находится в пределах радиуса цели, то возвращается True, иначе - False
     */
    bool test_goal();

    /*!
     * \brief Возвращает список позиций агентов
     * \return Список позиций агентов
     */
    QList<QPoint> get_agents_positions();

    /*!
     * \brief Возвращает объекты-преграды
     * \return Список указателей на все имеющиеся объекты-преграды
     */
    QList<COtherObject*> get_objects();

    /*!
     * \brief Возвращает указатель на определенный объект
     * \param index Номер объекта
     * \return Указатель на объект
     */
    COtherObject* get_object(int index);

    /*!
     * \brief Возвращает позицию пастуха
     * \return Координаты пастуха
     */
    QPoint get_shepherd_position();

    /*!
     * \brief Возвращает координаты цели
     * \return Координаты цели
     */
    QPoint get_goal();

    /*!
     * \brief Возвращает размеры поля
     * \return Точка, содержащая размеры поля
     */
    QPoint get_field_size();

    /*!
     * \brief Возвращает координаты цели в виде вектора
     * \return Вектор цели
     */
    QVector2D get_goal_position();

    static CAlgorithm algorithm; ///< алгоритм

private:
    /*!
     * \brief Удаляет всех имеющихся агентов
     */
    void clear_agents();

    /*!
     * \brief Задает новые направления агентов
     */
    void agent_behavior();

    /*!
     * \brief Находит промежуточные цели
     */
    void find_subgoal();

    /*!
     * \brief Генерирует случайное целое число
     * \param size Диапазон
     * \param offset Минимальное значение
     * \return Случайное целое число
     */
    int gen_random(int size, int offset);

    /*!
     * \brief Находит угол между двумя векторами
     * \param vector1 Первый вектор
     * \param vector2 Второй вектор
     * \return Угол между векторами
     */
    float get_angle(QVector2D vector1, QVector2D vector2);

    /*!
     * \brief Определяет локальный центр масс для подгруппы
     * \param position Позиция агента, относительно которого задается группа
     * \return Координаты локального цетра масс
     */
    QVector2D get_local_mass_center(QVector2D position);

    /*!
     * \brief Находит самого удаленного агента из списка относительно позиции
     * \param agents Список агентов
     * \param position Позиция, относительно которой выполняется поиск
     * \return Координаты самого удаленного агента относительно позиции
     */
    QVector2D get_furthest_agent(QList<CAgent*> agents, QVector2D position);

    /*!
     * \brief Находит ближайшего агента
     * \param agent Агент, для которого необходимо найти ближайшего соседа
     * \return Координаты ближайшего соседа агента
     */
    QVector2D get_nearest_agent(QVector2D agent);

    /*!
     * \brief Находит направление отталкивания агента от соседей
     * \param position Позиция агента
     * \return Направление отталкивания от других агентов
     */
    QVector2D get_repulsive_force(QVector2D position);

    /*!
     * \brief Генерирует случайное направление движения
     * \return Случайное направление движения
     */
    QVector2D get_error();

    /*!
     * \brief Поворачивает вектор на определенный угол
     * \param vector Исходный вектор
     * \param angle Угол поворота
     * \return Полученный вектор
     */
    QVector2D rotate_vector(QVector2D vector, int angle);

    /*!
     * \brief Находит центр масс агентов из списка
     * \param agents Список агентов
     * \return Координаты центра масс
     */
    QVector2D get_mass_center(QList<CAgent*> agents);

    /*!
     * \brief Находит направление агента, задающееся реакцией на объекты-преграды
     * \param position Координаты агента
     * \return Направление
     */
    QVector2D get_object_reaction(QVector2D position);

    /*!
     * \brief Находит направление агента, задающееся реакцией на границы поля
     * \param position Координаты объекта
     * \return Направление
     */
    QVector2D get_border_reaction(QVector2D position);

    /*!
     * \brief Возвращает список соседей, находящихся в радиусе реакции агента
     * \param position Позиция агента
     * \return Список соседей
     */
    QList<QVector2D> get_neighbours(QVector2D position);

    /*!
     * \brief Генерирует случайную координату
     * \return Точка
     *
     * Для генерации используются размеры области генерации агентов
     */
    QPoint gen_position();

    /*!
     * \brief Проверяет, свободна ли позиция для генерации
     * \param position Позизия генерируемого агента
     * \return Результат проверки
     *
     * Если на проверяемой позиции отсутствует агент, то возвращает True, иначе - False
     */
    bool test_position(QPoint position);

    /*!
     * \brief Проверяет новую позицию агента
     * \param old_position Старая позиция агента
     * \param new_position Новая позиция агента
     * \return Результат проверки
     *
     * Если новую позицию не занимает никакой другой агент, то возвращает True, иначе - False
     */
    bool test_position(QVector2D old_position, QVector2D new_position);

    /*!
     * \brief Проверяет на наличие препятствий на пути к цели
     */
    void test_object_position();

    /*!
     * \brief Проверяет возможность генерации заданного количества агентов на заданной площади
     * \return Результат проверки
     *
     * Возвращает True, если генерация возможна, иначе - False
     */
    bool test_gen_field();
    /*!
     * \brief Проверяет, находится ли объект в пределах радиуса от центра масс
     * \param point Координата объекта
     * \param global_mass_center Глобальный центр масс
     * \param radius Допустимый радиус
     * \return Результат проверки
     *
     * Возвращает True, если объект находится в пределах радиуса, иначе - False
     */
    bool test_distance(QVector2D point, QVector2D global_mass_center, int radius);

private:
    QList<CAgent*> agents; ///< Список агентов
    QList<COtherObject*> objects; ///< Список объектов преград

    CShepherd shepherd; ///< Пастух

    QVector2D goal; ///< Координаты цели
    QVector2D subgoal; ///< Координаты промежуточной цели

    CAgent* nearest_agent; ///< Указатель на текущего отбившегося агента

    QPoint gen_center; ///< Координаты центра генерации агентов
    QPoint gen_size; ///< Размеры поля генерации агентов
    QPoint field_size; ///< Размеры всего рабочего поля

    bool virtual_shepherd; ///< Тип пастуха
    bool driving; ///< Режим работы пастуха

    int agent_quantity; ///< Количество агентов
    int agent_nearest_quantity; ///< Количество ближайших соседей для агентов
    int agents_shepherd_reaction; ///< Радиус реакции на пастуха
    int agents_agent_reaction; ///< Радиус реакции на соседей
    int agents_other_reaction; ///< Радиус реакции на объекты-преграды
    int border_reaction; ///< Радиус реакции на границы рабочего поля
    int goal_radius; ///< Радиус цели

    int agent_size; ///< Размер агента

    double agents_agent_repulsion; ///< Сила отталкивания от соседей
    double agents_agent_attraction; ///< Сила притяжения к соседям
    double agents_shepherd_repulsion; ///< Сила отталкивания от пастуха
    double agents_other_repulsion; ///< Сила отталкивания от преград
    double agents_inertia; ///< Инерция
    double agents_noise; ///< Коэффициент шума для агентов
    double agents_movement_probability; ///< Вероятность случайных передвижений агентов
    double agent_speed; ///< Скорость передвижения агента
    double shepherd_speed; ///< Скорость передвижения пастуха
    double shepherd_noise; ///< Коэффициент шума для пастуха
};

#endif // CALGORITHM_H
