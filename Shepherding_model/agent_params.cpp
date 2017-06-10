#include "agent_params.h"
#include "ui_agent_params.h"

#include "model/algorithm.h"

CAgentParams::CAgentParams(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAgentParams)
{
    ui->setupUi(this);
}

CAgentParams::~CAgentParams()
{
    delete ui;
}

void CAgentParams::take_agent_params()
{
    CAlgorithm::algorithm.set_agent_quantity(ui->quantity->value());
    CAlgorithm::algorithm.set_agent_nearest_quantity(ui->quantity_nearest->value());
    CAlgorithm::algorithm.set_agents_agent_attraction(ui->agent_attraction->value());
    CAlgorithm::algorithm.set_agents_agent_reaction(ui->agent_reaction->value());
    CAlgorithm::algorithm.set_agents_agent_repulsion(ui->agent_repulsion->value());
    CAlgorithm::algorithm.set_agents_inertia(ui->inertia->value());
    CAlgorithm::algorithm.set_agents_movement_probability(ui->movement_probability->value());
    CAlgorithm::algorithm.set_agents_noise(ui->noise->value());
    CAlgorithm::algorithm.set_agents_other_reaction(ui->other_reaction->value());
    CAlgorithm::algorithm.set_agents_other_repulsion(ui->other_repulsion->value());
    CAlgorithm::algorithm.set_agents_shepherd_reaction(ui->shepherd_reaction->value());
    CAlgorithm::algorithm.set_agents_shepherd_repulsion(ui->shepherd_repulsion->value());
    CAlgorithm::algorithm.set_agent_speed(ui->speed->value());
}
