#include "algorithm.h"

#include <QTime>
#include <QVector2D>

CAlgorithm CAlgorithm::algorithm;

CAlgorithm::CAlgorithm()
{
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    virtual_shepherd = false;
    driving = false;

    agents_shepherd_reaction = 65;
    agents_agent_reaction = 2;
    agents_other_reaction = 2;
    border_reaction = 4;
    agent_quantity = 50;
    agent_nearest_quantity = 49;
    agent_size = 2;

    agents_agent_repulsion = 2.0;
    agents_agent_attraction = 1.05;
    agents_shepherd_repulsion = 1.0;
    agents_other_repulsion = 1.1;
    agents_inertia = 0.5;
    agents_noise = 0.3;
    agents_movement_probability = 0.05;
    agent_speed = 1.0;
    shepherd_speed = 1.5;
    shepherd_noise = 0.3;

    field_size = QPoint(500, 500);
    gen_center = QPoint(350, 350);
    gen_size = QPoint(150, 150);
    set_goal(QPoint(15, 15));

    goal_radius = agents_agent_reaction * sqrt(agent_quantity);

    gen_agents();
}

CAlgorithm::~CAlgorithm()
{
    clear_agents();
    clear_objects();
}

int CAlgorithm::get_goal_radius()
{
    return goal_radius;
}

void CAlgorithm::execution()
{
    QVector2D global_mass_center;

    global_mass_center = get_mass_center(agents);

    double index = 2.0 / 3.0;
    int group_radius = agents_agent_reaction * powf(agent_quantity, index);

    QVector2D furthest_agent;

    if (test_distance(nearest_agent->get_vector_position(), global_mass_center, group_radius))
    {
        furthest_agent = get_furthest_agent(agents, global_mass_center);
    }
    else
    {
        furthest_agent = nearest_agent->get_vector_position();
    }

    QVector2D position;

    if (test_distance(furthest_agent, global_mass_center, group_radius))
    {
        if (!driving)
        {
            find_subgoal();
        }

        driving = true;

        position = global_mass_center - subgoal;
        float position_factor = (agents_agent_reaction * sqrt(agent_quantity)) / position.length();
        position_factor += 1;
        position *= position_factor;
        position = position - (global_mass_center - subgoal);
        position = position + global_mass_center;
    }
    else
    {
        driving = false;

        position = furthest_agent - global_mass_center;
        float position_factor = agents_agent_reaction / position.length();
        position_factor += 1;
        position *= position_factor;
        position = position - (furthest_agent - global_mass_center);
        position = position + furthest_agent;

    }

    if (!virtual_shepherd)
    {
        position = position - shepherd.get_vector_position();
        position.normalize();

        double speed = shepherd_speed;

        if (test_distance(shepherd.get_vector_position(), furthest_agent, 3 * agents_agent_reaction))
        {
            speed = 0.3 * agents_agent_reaction;
        }

        position = position * speed + shepherd.get_vector_position();
        position += shepherd_noise * get_error();
    }

    shepherd.set_vector_position(position);

    agent_behavior();

}

void CAlgorithm::set_virtual_shepherd(bool flag)
{
    virtual_shepherd = flag;
}

void CAlgorithm::set_gen_center(QPoint gen_center)
{
    this->gen_center = gen_center;
}

void CAlgorithm::set_gen_size(QPoint size)
{
    this->gen_size = size;
}

void CAlgorithm::set_agent_quantity(int quantity)
{
    agent_quantity = quantity;

    agent_nearest_quantity = --quantity;
    goal_radius = agents_agent_reaction * sqrt(agent_quantity);
}

void CAlgorithm::clear_agents()
{
    while(!agents.isEmpty())
    {
        delete agents.takeFirst();
    }
}

void CAlgorithm::clear_objects()
{
    while(!objects.isEmpty())
    {
        delete objects.takeFirst();
    }
}

void CAlgorithm::set_goal(QPoint goal)
{
    this->goal.setX(goal.x());
    this->goal.setY(goal.y());

    subgoal = this->goal;
}

void CAlgorithm::set_agent_nearest_quantity(int quantity)
{
    agent_nearest_quantity = quantity;
}

void CAlgorithm::set_agents_agent_reaction(int radius)
{
    agents_agent_reaction = radius + agent_size;

    goal_radius = agents_agent_reaction * sqrt(agent_quantity);
}

void CAlgorithm::set_agents_shepherd_reaction(int radius)
{
    agents_shepherd_reaction = radius + shepherd.get_size();
}

void CAlgorithm::set_agents_other_reaction(int radius)
{
    agents_other_reaction = radius;
}

void CAlgorithm::set_agents_agent_repulsion(double strength)
{
    agents_agent_repulsion = strength;
}

void CAlgorithm::set_agents_agent_attraction(double strength)
{
    agents_agent_attraction = strength;
}

void CAlgorithm::set_agents_shepherd_repulsion(double strength)
{
    agents_shepherd_repulsion = strength;
}

void CAlgorithm::set_agents_other_repulsion(double strength)
{
    agents_other_repulsion = strength;
}

void CAlgorithm::set_agents_inertia(double inertia)
{
    agents_inertia = inertia;
}

void CAlgorithm::set_agents_noise(double noise)
{
    agents_noise = noise;
}

void CAlgorithm::set_agents_movement_probability(double probability)
{
    agents_movement_probability = probability;
}

void CAlgorithm::set_agent_speed(double speed)
{
    agent_speed = speed;
}

void CAlgorithm::set_shepherd_speed(double speed)
{
    shepherd_speed = speed;
}

void CAlgorithm::set_shepherd_noise(double noise)
{
    shepherd_noise = noise;
}

void CAlgorithm::add_object(QString name, QPoint position, int radius)
{
    COtherObject* object = new COtherObject;

    object->set_name(name);
    object->set_position(position);
    object->set_size(radius);

    objects.push_back(object);
}

void CAlgorithm::change_object(int index, QString name, QPoint position, int radius)
{
    if (index >= 0 && index < objects.length())
    {
        objects.at(index)->set_name(name);
        objects.at(index)->set_position(position);
        objects.at(index)->set_size(radius);
    }
}

void CAlgorithm::delete_object(int index)
{
    if (index >= 0 && index < objects.length())
    {
        delete objects.takeAt(index);
    }
}

bool CAlgorithm::gen_agents()
{
    if (!test_gen_field())
    {
        return false;
    }

    clear_agents();

    for (int i = 0; i < agent_quantity; i++)
    {
        CAgent* agent = new CAgent;
        agent->set_position(gen_position());
        agents.push_back(agent);
    }

    if (!agents.isEmpty())
    {
        nearest_agent = agents.first();

        test_object_position();

        return true;
    }

    return false;
}

bool CAlgorithm::gen_shepherd(QPoint position)
{
    shepherd.set_position(position);

    return true;
}

bool CAlgorithm::test_goal()
{
    QVector2D global_mass_center = get_mass_center(agents);

    QVector2D distance = global_mass_center - subgoal;

    if (distance.length() <= goal_radius)
    {
        if (goal == subgoal)
        {
            return true;
        }
        else
        {
            subgoal = goal;
            test_object_position();
        }
    }

    return false;
}

QList<QPoint> CAlgorithm::get_agents_positions()
{
    QList<QPoint> positions;

    QList<CAgent*>::Iterator i;

    for (i = agents.begin(); i != agents.end(); i++)
    {
        positions.push_back((*i)->get_position());
    }

    return positions;
}

QList<COtherObject *> CAlgorithm::get_objects()
{
    return objects;
}

COtherObject *CAlgorithm::get_object(int index)
{
    if (index >= 0 && index < objects.length())
    {
        return objects.at(index);
    }

    return new COtherObject;
}

QPoint CAlgorithm::get_shepherd_position()
{
    return shepherd.get_position();
}

QPoint CAlgorithm::get_goal()
{
    return QPoint(subgoal.x(), subgoal.y());
}

QPoint CAlgorithm::get_field_size()
{
    return field_size;
}

QVector2D CAlgorithm::get_goal_position()
{
    return goal;
}

void CAlgorithm::agent_behavior()
{
    QList<CAgent*>::Iterator i;

    QVector2D direction;
    QVector2D local_mass_center;// = get_mass_center(agents);
    QVector2D position;
    QVector2D strength;
    QVector2D agent;

    agent_nearest_quantity = agent_quantity - 1;

    for (i = agents.begin(); i != agents.end(); i++)
    {
        position = (*i)->get_vector_position();
        agent = get_nearest_agent(position);

        direction = (*i)->get_direction() * agents_inertia;

        if (QVector2D(position - shepherd.get_vector_position()).length() <= agents_shepherd_reaction)
        {
            local_mass_center = get_local_mass_center(position);
            strength = local_mass_center - position;
            strength.normalize();
            direction += agents_agent_attraction * strength;

            strength = position - shepherd.get_vector_position();
            strength.normalize();
            direction += agents_shepherd_repulsion * strength;
            direction.normalize();
        }
        else if (QVector2D(agent - position).length() > agents_agent_reaction)
        {
            continue;
        }

        strength = get_repulsive_force(position);
        strength.normalize();
        direction += agents_agent_repulsion * strength;

        direction += agents_other_repulsion * get_object_reaction(position);

        strength = get_border_reaction(position);
        strength.normalize();
        direction += border_reaction * strength;

        strength = get_error();
        strength.normalize();
        direction += agents_noise * strength;
        direction.normalize();

        do
        {
            position = position + agent_speed * direction;
            direction = rotate_vector(direction, 30);
        } while (!test_position((*i)->get_vector_position(), position));


        (*i)->set_vector_position(position);
        (*i)->set_direction(direction);
    }
}

void CAlgorithm::find_subgoal()
{
    QVector2D save = subgoal;

    subgoal = goal;

    test_object_position();

    if (subgoal != goal)
    {
        subgoal = save;
    }
}

int CAlgorithm::gen_random(int size, int offset)
{
    if (size == 0)
    {
        return 0;
    }

    int result = qrand() % size + offset;

    if (result < 0)
    {
        return 0;
    }

    return result;
}

float CAlgorithm::get_angle(QVector2D vector1, QVector2D vector2)
{
    float result = vector1.x() * vector2.x() + vector1.y() * vector2.y();

    result /= vector1.length() * vector2.length();

    return result;
}

QVector2D CAlgorithm::get_local_mass_center(QVector2D position)
{
    QList<CAgent*> agents = this->agents;
    //QList<CAgent*> nearest;

    QVector2D agent;

    //CAgent* min_agent;

    //int min_distance = field_size.x();
    //int distance = 0;
    //int index = 0;

    //while (nearest.length() < agent_nearest_quantity)
    //{
        //min_distance = field_size.x();

        for (int i = 0; i < agents.length(); i++)
        {
            agent = agents.at(i)->get_vector_position();

            if (agent == position)
            {
                agents.takeAt(i);
                //i--;
                break;
            }

            //agents.takeAt(agents.indexOf(get_furthest_agent(agents, agent)));
            //i--;

            /*agent = agent - position;
            distance = agent.length();

            if (distance < min_distance)
            {
                min_distance = distance;
                min_agent = agents.at(i);
                index = i;
            }*/
        }

        //agents.takeAt(index);
        //nearest.push_back(min_agent);
    //}

    //return get_mass_center(nearest);
        return get_mass_center(agents);
}

QPoint CAlgorithm::gen_position()
{
    QPoint position;
    int x = 0;
    int y = 0;

    do
    {
        x = gen_random(gen_size.x(), gen_center.x() - gen_size.x() / 2);
        position.setX(x);
        y = gen_random(gen_size.y(), gen_center.y() - gen_size.y() / 2);
        position.setY(y);
    }while (!test_position(position));

    return position;
}

QVector2D CAlgorithm::get_furthest_agent(QList<CAgent*> agents, QVector2D position)
{
    QVector2D result;
    QVector2D segment;
    int distance = 0;
    int max_distance = 0;

    QList<CAgent*>::Iterator i;

    for (i = agents.begin(); i != agents.end(); i++)
    {
        segment = (*i)->get_vector_position() - position;
        distance = segment.length();

        if (distance > max_distance)
        {
            max_distance = distance;
            result = (*i)->get_vector_position();
        }
    }

    return result;
}

QVector2D CAlgorithm::get_nearest_agent(QVector2D agent)
{
    QVector2D nearest;

    QVector2D segment;
    int distance = 0;
    int min_distance = agents.first()->get_vector_position().length();

    QList<CAgent*>::Iterator i;

    for (i = agents.begin(); i != agents.end(); i++)
    {
        segment = (*i)->get_vector_position();

        if (segment == agent)
        {
            continue;
        }

        segment -= agent;
        distance = segment.length();

        if (distance < min_distance)
        {
            min_distance = distance;
            nearest = (*i)->get_vector_position();
        }
    }

    return nearest;
}

QVector2D CAlgorithm::get_repulsive_force(QVector2D position)
{
    QVector2D result;
    QVector2D neighbour;
    QList<QVector2D> neighbours = get_neighbours(position);

    while (!neighbours.isEmpty())
    {
        neighbour = neighbours.takeFirst();
        neighbour = position - neighbour;
        result += neighbour / neighbour.length();
    }

    return result;
}

QVector2D CAlgorithm::get_error()
{
    int radius = 10;
    int x = qrand() % radius - radius/2;
    int y = radius * radius - x * x;
    y = sqrt(y);

    if (qrand() % 2)
    {
        y *= -1;
    }

    QVector2D result;
    result.setX(x);
    result.setY(y);
    result.normalize();

    return result;
}

QVector2D CAlgorithm::rotate_vector(QVector2D vector, int angle)
{
    double rad_angle = angle * (22.0 / 7.0) / 180.0;

    vector.setX(vector.x() * cos(rad_angle) - vector.x() * sin(rad_angle));
    vector.setY(vector.y() * sin(rad_angle) + vector.y() * cos(rad_angle));

    return vector;
}

QVector2D CAlgorithm::get_mass_center(QList<CAgent *> agents)
{
    QList<int> x;
    QList<int> y;

    QList<CAgent*>::Iterator i;

    for (i = agents.begin(); i != agents.end(); i++)
    {
        x.push_back((*i)->get_vector_position().x());
        y.push_back((*i)->get_vector_position().y());
    }

    qSort(x.begin(), x.end());
    qSort(y.begin(), y.end());

    int index = agent_quantity / 2;

    QVector2D result;

    if (!x.isEmpty() && !y.isEmpty())
    {
        result.setX(x.at(index));
        result.setY(y.at(index));
    }

    return result;
}

QVector2D CAlgorithm::get_object_reaction(QVector2D position)
{
    QList<COtherObject*>::Iterator i;

    QVector2D distance;
    QVector2D direction;

    for (i = objects.begin(); i != objects.end(); i++)
    {
        distance = position - (*i)->get_vector_position();

        if ((distance.length() - (*i)->get_size()) < agents_other_reaction)
        {
            direction += distance;
        }
    }

    direction.normalize();

    return direction;
}

QVector2D CAlgorithm::get_border_reaction(QVector2D position)
{
    QVector2D direction;

    if (position.x() - border_reaction <= 0)
    {
        direction.setX(border_reaction);
    }
    else if (position.x() + border_reaction >= field_size.x())
    {
        direction.setX(-1 * border_reaction);
    }
    else if (position.y() - border_reaction <= 0)
    {
        direction.setY(border_reaction);
    }
    else if (position.y() + border_reaction >= field_size.y())
    {
        direction.setY(-1 * border_reaction);
    }

    return direction;
}

QList<QVector2D> CAlgorithm::get_neighbours(QVector2D position)
{
    QList<QVector2D> result;
    QVector2D distance;

    QList<CAgent*>::Iterator i;

    for (i = agents.begin(); i != agents.end(); i++)
    {
        if ((*i)->get_vector_position() == position)
        {
            continue;
        }

        distance = (*i)->get_vector_position() - position;

        if (distance.length() < agents_agent_reaction)
        {
            result.push_back((*i)->get_vector_position());
        }
    }

    return result;
}

bool CAlgorithm::test_position(QPoint position)
{
    int agent_x = 0;
    int agent_y = 0;
    int agent_size = 0;

    QList<CAgent*>::Iterator i;

    for (i = agents.begin(); i != agents.end(); i++)
    {
        agent_x = (*i)->get_position().x();
        agent_y = (*i)->get_position().y();
        agent_size = (*i)->get_size();
        agent_size = agent_size*2 + agent_size / 2;

        if (agent_x - agent_size <= position.x() &&
            agent_x + agent_size >= position.x() &&
            agent_y - agent_size <= position.y() &&
            agent_y + agent_size >= position.y())
        {
            return false;
        }
    }

    return true;
}

bool CAlgorithm::test_position(QVector2D old_position, QVector2D new_position)
{
    int agent_x = 0;
    int agent_y = 0;
    int agent_size = 0;

    QList<CAgent*>::Iterator i;

    for (i = agents.begin(); i != agents.end(); i++)
    {
        if (old_position == (*i)->get_vector_position())
        {
            continue;
        }

        agent_x = (*i)->get_position().x();
        agent_y = (*i)->get_position().y();
        agent_size = (*i)->get_size();

        if (agent_x - agent_size <= new_position.x() &&
            agent_x + agent_size >= new_position.x() &&
            agent_y - agent_size <= new_position.y() &&
            agent_y + agent_size >= new_position.y())
        {
            return false;
        }
    }

    return true;
}

void CAlgorithm::test_object_position()
{
    QList<COtherObject*>::Iterator i;

    QVector2D mass_center = get_mass_center(agents);
    QVector2D goal_distance = subgoal - mass_center;
    QVector2D object_distance;
    QVector2D x;
    x.setX(1);

    float angle;
    float distance;
    float critical_point_distance;
    int object_size = 0;
    float group_radius = agents_agent_reaction * agents.first()->get_size() * 2;

    for (i = objects.begin(); i != objects.end(); i++)
    {
        object_distance = (*i)->get_vector_position() - mass_center;
        angle = get_angle(object_distance, goal_distance);
        angle = acos(angle);
        distance = object_distance.length() * sin(angle);
        object_size = (*i)->get_size();

        if ((distance <= object_size && object_distance.length() < goal_distance.length()) ||
            QVector2D(subgoal - (*i)->get_vector_position()).length() <= object_size)
        {
            critical_point_distance = object_distance.length() * cos(angle);
            distance = object_size - distance + group_radius;
            angle += atan(distance / critical_point_distance);
            angle *= 180.0 / (22.0 / 7.0);

            if (get_angle(goal_distance, x) < get_angle(object_distance, x))
            {
                angle = -angle;
            }

            object_distance = rotate_vector(object_distance, angle);

            if (subgoal == mass_center + object_distance)
            {
                subgoal = mass_center + rotate_vector(object_distance, -2 * angle);
                return;
            }
            else
            {
                subgoal = mass_center + object_distance;
            }

            test_object_position();
            return;
        }
    }
}

bool CAlgorithm::test_gen_field()
{
    int x = gen_center.x() - gen_size.x() / 2;
    if (x < 0)
    {
        x += gen_size.x() * 2;
    }
    else
    {
        x = gen_size.x();
    }

    int y = gen_center.y() - gen_size.y() / 2;
    if (y < 0)
    {
        y += gen_size.y() * 2;
    }
    else
    {
        y = gen_size.y();
    }

    x /= 5;
    y /= 5;

    int gen_squar = 6 * x * y / 13;

    if (agent_quantity < gen_squar)
    {
        return true;
    }

    return false;
}

bool CAlgorithm::test_distance(QVector2D point, QVector2D global_mass_center, int radius)
{
    QVector2D distance = point - global_mass_center;

    if (distance.length() < radius)
    {
        return true;
    }

    return false;
}
