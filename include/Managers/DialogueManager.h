#pragma once

#include "../Base/Singleton.h"
#include <string>
#include <map>

class DialogueManager : public Singleton<DialogueManager>
{
public:
    DialogueManager();
    void Init();
    void ShowDialogue(const std::string& key);
    void ShowStory(const std::vector<std::string>& dialogueKeys);

private:
    std::map<std::string, std::string> _dialogues;
    friend class Singleton<DialogueManager>;
};