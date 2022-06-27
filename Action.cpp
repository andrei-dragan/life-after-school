#include "Action.h"

void ActionAdd::executeUndo() {
	this->model.removeEvent(this->addedEvent.getTitle(), this->addedEvent.getDate());
}

void ActionAdd::executeRedo() {
	this->model.addEvent(this->addedEvent.getTitle(), this->addedEvent.getDescription(), this->addedEvent.getLink(), this->addedEvent.getAttendance(), this->addedEvent.getDate());
}

void ActionRemove::executeUndo() {
	this->model.addEvent(this->deletedEvent.getTitle(), this->deletedEvent.getDescription(), this->deletedEvent.getLink(), this->deletedEvent.getAttendance(), this->deletedEvent.getDate());
}

void ActionRemove::executeRedo() {
	this->model.removeEvent(this->deletedEvent.getTitle(), this->deletedEvent.getDate());
}

void ActionUpdate::executeUndo() {
	this->model.updateEvent(this->newE.getTitle(), this->newE.getDate(), this->oldE.getDescription(), this->oldE.getLink());
}

void ActionUpdate::executeRedo() {
	this->model.updateEvent(this->oldE.getTitle(), this->oldE.getDate(), this->newE.getDescription(), this->newE.getLink());
}