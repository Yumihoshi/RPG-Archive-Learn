/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/7/1 下午2:10
* @version: 1.0
* @description: 
*******************************************************************************/
#include "../../include/Archive/Archive.h"

bool Archive::CheckIdValid() const
{
    return _id >=1 && _id <= 3;
}
