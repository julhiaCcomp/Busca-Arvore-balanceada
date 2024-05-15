class No:
    def __init__(self, chave):
        self.chave = chave
        self.esquerda = None
        self.direita = None
        self.altura = 1


class ArvoreAVL:
    def inserir(self, raiz, chave):
        if not raiz:
            return No(chave)
        elif chave < raiz.chave:
            raiz.esquerda = self.inserir(raiz.esquerda, chave)
        else:
            raiz.direita = self.inserir(raiz.direita, chave)

        raiz.altura = 1 + max(self.get_altura(raiz.esquerda), self.get_altura(raiz.direita))

        # Verificar o balanceamento do nó
        balanceamento = self.get_balanceamento(raiz)

        # Caso de rotação simples à esquerda
        if balanceamento > 1 and chave < raiz.esquerda.chave:
            return self.rotacao_direita(raiz)

        # Caso de rotação simples à direita
        if balanceamento < -1 and chave > raiz.direita.chave:
            return self.rotacao_esquerda(raiz)

        # Caso de rotação dupla à esquerda
        if balanceamento > 1 and chave > raiz.esquerda.chave:
            raiz.esquerda = self.rotacao_esquerda(raiz.esquerda)
            return self.rotacao_direita(raiz)

        # Caso de rotação dupla à direita
        if balanceamento < -1 and chave < raiz.direita.chave:
            raiz.direita = self.rotacao_direita(raiz.direita)
            return self.rotacao_esquerda(raiz)

        return raiz

    def rotacao_esquerda(self, z):
        y = z.direita
        T2 = y.esquerda

        # Realizar rotação
        y.esquerda = z
        z.direita = T2

        # Atualizar alturas
        z.altura = 1 + max(self.get_altura(z.esquerda), self.get_altura(z.direita))
        y.altura = 1 + max(self.get_altura(y.esquerda), self.get_altura(y.direita))

        return y

    def rotacao_direita(self, z):
        y = z.esquerda
        T3 = y.direita

        # Realizar rotação
        y.direita = z
        z.esquerda = T3

        # Atualizar alturas
        z.altura = 1 + max(self.get_altura(z.esquerda), self.get_altura(z.direita))
        y.altura = 1 + max(self.get_altura(y.esquerda), self.get_altura(y.direita))

        return y

    def get_altura(self, no):
        if not no:
            return 0
        return no.altura

    def get_balanceamento(self, no):
        if not no:
            return 0
        return self.get_altura(no.esquerda) - self.get_altura(no.direita)

    def pre_ordem(self, raiz):
        if raiz:
            print("{0} ".format(raiz.chave), end="")
            self.pre_ordem(raiz.esquerda)
            self.pre_ordem(raiz.direita)

    def buscar(self, raiz, chave):
        if not raiz or raiz.chave == chave:
            return raiz

        if raiz.chave < chave:
            return self.buscar(raiz.direita, chave)

        return self.buscar(raiz.esquerda, chave)


# Exemplo de uso
arvore = ArvoreAVL()
raiz = None

raiz = arvore.inserir(raiz, 10)
raiz = arvore.inserir(raiz, 20)
raiz = arvore.inserir(raiz, 30)
raiz = arvore.inserir(raiz, 40)
raiz = arvore.inserir(raiz, 50)
raiz = arvore.inserir(raiz, 25)

print("Percurso Pre-Ordem da Árvore AVL construída:")
arvore.pre_ordem(raiz)

chave_busca = 30
resultado_busca = arvore.buscar(raiz, chave_busca)
if resultado_busca:
    print(f"\nChave {chave_busca} encontrada na árvore AVL.")
else:
    print(f"\nChave {chave_busca} não encontrada na árvore AVL.")
