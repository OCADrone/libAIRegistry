#ifndef LIBAIREGISTRY_COMMANDS_HH
#define LIBAIREGISTRY_COMMANDS_HH

namespace AIRegistry
{
	/**
	 * Registry client <-> server commands.
	 */
	enum commands
	{
		CTRL,					/**< Test connection. */
		READ,					/**< Get key value. */
		WRITE,				/**< Update key value. */
		MKNODE,				/**< Insert a node. */
		MKLEAF,				/**< Insert a leaf. */
		ISNODE,				/**< Check if a node exists. */
		ISLEAF,				/**< Check if a leaf exists. */
		SIZE					/**< Return path size. */
	};
}

#endif
