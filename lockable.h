#ifndef LOCKABLE_H
#define LOCKABLE_H
#include<string>

class Lockable {
	protected:
		bool locked;
		std::string password;
		/**
		 * @name Password Authenticator
		 * @brief Matches provided password to saved password.
		 * @param pswd The password provided by the user.
		 * @return true if the password is correct, false if not.
		 *
		 * Matches provided password to saved password and returns whether the two passwords match.
		 */
        bool authenticate(std::string pswd);

	public:
		Lockable();

		/**
		 * @name Locked Status Getter
		 * @brief Returns whether the object is locked.
		 * @return true if the object is locked, false if unlocked.
		 *
		 * Returns whether the object is locked.
		 */
		bool isLocked();
		/**
		* @name Object Unlocker
		* @brief Attempts to unlock the object with the provided password.
		* @param pswd Password to attempt to unlock the object.
		* @return true if the object becomes unlocked, false if the object stays locked.
		*
		* Attempts to unlock the object with the provided password.
		*/
        bool unlock(std::string pswd);
		/**
		* @name Object Locker
		* @brief Locks the object.
		* @return true if the object becomes locked, false if the object stays unlocked.
		*
		* Locks the object.
		*/
        bool lock();
		/**
		* @name Object Locker
		* @brief Locks the object and sets the password to the provided password.
		* @param pswd Password to lock the object with.
		* @return true if the object becomes locked, false if the object stays unlocked.
		*
		* Locks the object and sets the password to the provided password.
		*/
		bool lock(std::string pswd);
};
#endif
