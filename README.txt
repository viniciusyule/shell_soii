INTRODUÇÂO
	O shell desenvolvido é interativo que aceita comandos com 10 argumentos no máximo.
	Possui historico como diferencial, sem limite de entradas. Suporta multiplos pipes,
	bem como redirecionamente de E/S, controle de jobs, etc. Possui uma certa variedade 
	comandos embutidos(listados abaixo).
FUNCIONALIDADES
	IMPLEMENTADAS:
		-Comandos embutidos: fg, bg, kill, pwd, cd, jobs, history, use
		-Redirecionamento de E/S
		-Pipes
		-Execução em background e em foreground
		-Controle de jobs
		-Histórico*
*USO DO HISTÓRICO
	Descricao dos comandos: 
		-history: mostra o históricos dos comandos digitados no shell com os seus respectivos indices;
        	-use <indice do comando no histórico>: usa o comando de índice <índice>
	Exemplo de uso:
		[1] ls -la | grep teste (saida do comando history)
		use 1
	Combinacoes:
		É possível realizar algumas combinações com o comando use. Por exemplo:
		[1] ls -la 
		use 1 | sort > saida
		
CONSIDERAÇÕES: 
	-No código da shell, os nomes "job" e "process" foram trocados. Portanto, considere, ao ler
	o código que "process" se refere a "job" e vice-e-versa;
	-Não conseguimos gerar a imagem do profiler;
	-Não conseguimos usar o doxygen, por isso documentamos o código da maneira usual.

DESENVOLVEDORES:
	Vinicius dos Santos Martins #USP: 7123959
	Yule Vaz		    #USP: 5881819
