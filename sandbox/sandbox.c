/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:00:25 by kjikuhar          #+#    #+#             */
/*   Updated: 2025/07/02 21:23:35 by kjikuhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/* 関数プロトタイプ宣言 */
void	SetSignal(int SignalName);
void	SignalHandler(int SignalName);

int	main(void)
{
	SetSignal(SIGINT);
	SetSignal(SIGQUIT);
	while (1)
	{
		printf("実行中!!\n");
		sleep(3);
	}
	return (0);
}

/* シグナルの設定 */
void	SetSignal(int pSignalName)
{
	if (signal(pSignalName, SignalHandler) == SIG_ERR)
	{
		/* シグナル設定エラー  */
		printf("シグナルの設定が出来ませんでした。終了します。\n");
		exit(1);
	}
	return ;
}

/* シグナル・ハンドラー */
void	SignalHandler(int pSignalName)
{
	char	ans;

	printf("割り込みを受け付けました。\n");
	if (pSignalName == SIGQUIT)
	{
		printf("直ちに終了します。\n");
		exit(0);
	}
	else
	{
		printf("終了しますか？（Y/N）==> ");
		scanf("%c%*c", &ans);
		if (ans == 'Y' || ans == 'y')
		{
			printf("直ちに終了します。\n");
			exit(0);
		}
		else
		{
			/* シグナルの再設定 */
			SetSignal(pSignalName);
		}
	}
	return ;
}
