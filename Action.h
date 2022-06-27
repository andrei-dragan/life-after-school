#pragma once
#include "EventRepo.h"
#include "AdminModel.h"

class Action {
public:
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
	virtual ~Action() {};
};

class ActionAdd : public Action {
private:
	Event addedEvent;
	EventRepo& repo;
	AdminModel& model;
public:
	ActionAdd(Event _addedEvent, EventRepo& _repo, AdminModel& _model) : addedEvent{ _addedEvent }, repo{ _repo }, model{ _model } {};
	void executeUndo() override;
	void executeRedo() override;
	~ActionAdd() override {};
};

class ActionRemove : public Action {
private:
	Event deletedEvent;
	EventRepo& repo;
	AdminModel& model;
public:
	ActionRemove(Event _deletedEvent, EventRepo& _repo, AdminModel& _model) : deletedEvent{ _deletedEvent }, repo{ _repo }, model{ _model } {};
	void executeUndo() override;
	void executeRedo() override;
	~ActionRemove() override {};
};

class ActionUpdate : public Action {
private:
	Event oldE;
	Event newE;
	EventRepo& repo;
	AdminModel& model;
public:
	ActionUpdate(Event _oldE, Event _newE, EventRepo& _repo, AdminModel& _model) : oldE{ _oldE }, newE{ _newE }, repo{ _repo }, model{ _model } {};
	void executeUndo() override;
	void executeRedo() override;
	~ActionUpdate() override {};
};