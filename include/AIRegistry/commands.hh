#ifndef LIBAIREGISTRY_COMMANDS_HH
#define LIBAIREGISTRY_COMMANDS_HH

namespace AIRegistry
{
	/**
	 * Registry client <-> server commands.
	 * Faster and safer than command-as-string.
	 */
	enum commands
	{
		CTRL,		/**< Test connection. */
		READ,		/**< Get key value. */
		WRITE,		/**< Update key value. */
		MKNODE,		/**< Insert a node. */
		CHECK		/**< Check if a key exists. */
	};
}

#endif