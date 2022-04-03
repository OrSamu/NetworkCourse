#include "clientUtils.h"

void main()
{
	bool keepClientAlive = true;

	while (keepClientAlive)
	{
		int usersRequest = getUserRequest();

		switch (usersRequest)
		{
		case 0:
			keepClientAlive = false;
			closeClient();
			break;

		default :
			keepClientAlive = false;
			cout << "user selection was " << usersRequest << endl;
			break;
		}
	}
}