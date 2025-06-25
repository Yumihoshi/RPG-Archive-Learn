#pragma once
#include <map>
#include <vector>
#include "Singleton.h"
#include "Types.h"
#include "BasePokeModel.h"

using namespace std;

class PokeManager:public Singleton<PokeManager>
{
public:
    /// <summary>
    /// ��ӱ����ε���ӦԪ�����͵�������
    /// </summary>
    /// <param name="elementType">������Ԫ������</param>
    /// <param name="model">������ģ��ָ��</param>
    void AddPoke(ElementType elementType, shared_ptr<BasePokeModel> model)
    {
        // ���Ԫ�������Ƿ��Ѵ�����map��
        if (_pokeMap.find(elementType) == _pokeMap.end())
        {
            // ��������ڣ�����һ���µ�vector
            _pokeMap[elementType] = vector<shared_ptr<BasePokeModel>>();
        }

        // ����������ӵ���ӦԪ�����͵�vector��
        _pokeMap[elementType].push_back(model);
    }

    /// <summary>
    /// ��ȡָ��Ԫ�����͵����б�����
    /// </summary>
    /// <param name="elementType">Ԫ������</param>
    /// <returns>������ָ���vector</returns>
    vector<shared_ptr<BasePokeModel>> GetPokesByElement(ElementType elementType)
    {
        if (_pokeMap.find(elementType) != _pokeMap.end())
        {
            return _pokeMap[elementType];
        }
        return vector<shared_ptr<BasePokeModel>>(); // ���ؿ�vector
    }

    /// <summary>
    /// ��ȡ���б�����
    /// </summary>
    /// <returns>�������б����ε�map</returns>
    map<ElementType, vector<shared_ptr<BasePokeModel>>> GetAllPokes()
    {
        return _pokeMap;
    }

    /// <summary>
    /// ɾ��������
    /// </summary>
    /// <param name="elementType"></param>
    /// <returns></returns>
    bool RemovePokesByElement(ElementType elementType)
    {
        return _pokeMap.erase(elementType) > 0;
    }

    /// <summary>
    /// ɾ���ض��ı�����
    /// </summary>
    /// <param name="model">Ҫɾ���ı�����ָ��</param>
    /// <returns>�Ƿ��ҵ���ɾ��</returns>
    bool RemoveSpecificPoke(shared_ptr<BasePokeModel> model)
    {
        for (auto& pair : _pokeMap) {
            auto& pokeVector = pair.second;
            auto it = find(pokeVector.begin(), pokeVector.end(), model);
            if (it != pokeVector.end()) {
                pokeVector.erase(it);
                return true;
            }
        }
        return false;
    }

    /// <summary>
    /// ������б�����
    /// </summary>
    void ClearAllPokes()
    {
        _pokeMap.clear();
    }

private:
	friend class Singleton<PokeManager>;
	map < ElementType, vector<shared_ptr<BasePokeModel> >> _pokeMap;
	PokeManager();
};