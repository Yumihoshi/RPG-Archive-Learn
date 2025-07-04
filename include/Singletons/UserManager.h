/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/7/2 下午2:27
* @version: 1.0
* @description: 
*******************************************************************************/
#ifndef RPG_USERMANAGER_H
#define RPG_USERMANAGER_H

#include "../User/User.h"
#include "../Base/Singleton.h"

class UserManager : public Singleton<UserManager>
{
public:
    std::shared_ptr<User>
    login(const std::string &username, const std::string &password);

    void registerUser(const std::string &username, const std::string &password,
                      User::UserType type);

    void saveUsers();

    void loadUsers();

    // 管理员
    void createUser(const std::string &username, const std::string &password,
                    User::UserType type);

    void deleteUser(const std::string &username);

    void updateUserPassword(const std::string &username,
                            const std::string &newPassword);

    void listAllUsers() const;

    std::shared_ptr<User> getUserByUsername(const std::string &username) const;

    // 管理员对普通用户宝可梦的装备管理
    void equipPokemonAccessory(const std::string &username, int saveSlotIndex,
                               int pokemonIndex,
                               std::shared_ptr<Accessory> accessory);

    void unequipPokemonAccessory(const std::string &username, int saveSlotIndex,
                                 int pokemonIndex);

    void equipPokemonArmor(const std::string &username, int saveSlotIndex,
                           int pokemonIndex, std::shared_ptr<Armor> armor);

    void unequipPokemonArmor(const std::string &username, int saveSlotIndex,
                             int pokemonIndex);

    void listPokemonEquipment(const std::string &username, int saveSlotIndex,
                              int pokemonIndex) const;

private:
    std::map<std::string, std::shared_ptr<User>> users; // Map username to User object

    // Helper to get file path for user data
    std::string getUserDataFilePath() const;

    UserManager();

    friend class Singleton<UserManager>;
};


#endif //RPG_USERMANAGER_H
