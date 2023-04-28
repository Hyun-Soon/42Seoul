/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:08:25 by hyuim             #+#    #+#             */
/*   Updated: 2023/04/28 20:29:34 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			read_size;
	char		buf[BUFFER_SIZE + 1];
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	// TODO :: buf 초기화
	// TODO :: backup에 \n 있으면 read 건너뛰고 출력하기
	read_size = read(fd, buf, BUFFER_SIZE);
	if (read_size < 0) // <<<<- 여여기기서  <= 를 <로 바꿨더니 에러 긴메시지 엄청 뜸.
		return (NULL);
	buf[read_size] = 0;
	while (read_size > 0)
	{
		backup = gnl_strcat(backup, buf, read_size);
		if (!backup)
			return (NULL);
		if (find_nl(backup) >= 0)
			break ;
		read_size = read(fd, buf, BUFFER_SIZE);
	}
	if (read_size == -1)
		return (NULL);
	if (read_size == 0)
		return (backup);
	return (backup_slice(&backup, find_nl(backup)));
}

// #include <stdio.h>
// int main()
// {
// 	int fd;
// 	fd = open("./nl", O_RDONLY);
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	return 0;
// }

/*
버버퍼퍼에  \n이 남아있는 경우를 생각해라!!!!!
*/

/*
--------------------Mandatory-------------------
1. gnl 함수 한번 실행될 때 마다 fd에서 한줄씩 읽어야 함
2. 읽은 line을 리턴, 읽을 게 없거나 에러 발생 시 NULL 리턴
3. 파일을 읽던, standarad input으로 받던 잘 작동해야 한다.
4. 파일 끝에 도달했는데 \n으로 끝나지 않는 경우를 제외하면,
	returned line은 \n을 끝에 포함해야 한다.
5. header파일은 get_next_line()을 포함하고 있어야 함.
6. 모든 helper funcs는 get_next_line_utils.c에 넣어야 한다.
7. 문제 풀기 전에 static variable이 뭔지 알아봐라.
8. -D BUFFER_SIZE=n 옵션을 compiler call에 넣어놔라.
	이 버퍼 사이즈는 평가자가 테스트를 위해 정할 것이다.
9. -D BUFFER_SIZE 옵션을 사용하던 안하던 실행가능해야 한다. 즉, default 값을 정해놔라.
10. ex) cc -Wall -Wextra -Werror -D BUUFER_SIZE=42 <files>.c
11. gnl이 실행될 때마다 가능한 한 적게 읽어라. 새로운 라인을 만나면 현재 라인을 리턴해야 한다.
	전체 파일을 읽고 각 라인을 프로세싱하지 마라.
12. libft 사용 불가
13. lseek() 사용 불가
14. 전역 변수 사용 불가

---------------------Bonus-----------------------
1. get_next_line()이 오직 하나의 static variable만 사용해야 한다.
2. get_next_line()이 다수의 fd를 동시에 관리할 수 있어야 한다.
*/