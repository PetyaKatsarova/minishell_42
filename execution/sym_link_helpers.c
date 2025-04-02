// #include "../includes/minishell.h"

// // Detect if path is a symlink
// int is_symlink(const char *path)
// {
// 	struct stat info;
// 	if (lstat(path, &info) == -1)
// 		return (0);
// 	return (S_ISLNK(info.st_mode));
// }

// // Check if symlink is broken (target does not exist)
// int is_broken_symlink(const char *path)
// {
// 	struct stat link_info, target_info;

// 	if (lstat(path, &link_info) == -1)
// 		return (0);
// 	if (!S_ISLNK(link_info.st_mode))
// 		return (0);
// 	// stat fails if the symlink target doesn't exist
// 	if (stat(path, &target_info) == -1)
// 		return (1);
// 	return (0);
// }

// // Warn if cd path is a broken symlink
// int cd_warn_if_symlink(const char *path)
// {
// 	if (is_symlink(path))
// 	{
// 		if (is_broken_symlink(path))
// 		{
// 			printf("minishell: warning: '%s' is a broken symlink\n", path);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }
