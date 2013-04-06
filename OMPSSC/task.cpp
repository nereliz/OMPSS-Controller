#include "task.h"

Task::Task()
{
}
Task::~Task()
{
}

void Task::run(){
    emit this->requestCommunicate( this->socketDescriptor );
}
