#pragma once

#include "Singleton.h"

class DialogueManager : public Singleton<DialogueManager>
{
private:
    friend class Singleton<DialogueManager>;
    DialogueManager();
};

