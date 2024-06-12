
    <style>
        body {
            font-family: Arial, sans-serif;
            line-height: 1.6;
        }
        h1, h2 {
            color: #2c3e50;
        }
        pre {
            background-color: #f4f4f4;
            padding: 10px;
            border: 1px solid #ddd;
            overflow-x: auto;
        }
    </style>
</head>
<body>
    <h1>Descrição do Código do Robô Seguidor de Linha com Sensores de Cor e Ultrassônicos</h1>

    <h2>Componentes Utilizados:</h2>
    <ul>
        <li><strong>Sensor de Cor:</strong> Utilizado para detectar a cor da linha e determinar a trajetória do robô.</li>
        <li><strong>Sensores Ultrassônicos:</strong> Um sensor à frente para detectar obstáculos frontais e outro nos lados para detectar obstáculos laterais.</li>
        <li><strong>Motores:</strong> Controlam o movimento das rodas do robô.</li>
        <li><strong>Microcontrolador:</strong> Arduino ou similar para processar as informações dos sensores e controlar os motores.</li>
    </ul>

    <h2>Funcionamento do Código:</h2>
    <h3>1. Inicialização:</h3>
    <p>Configuração dos pinos dos sensores de cor e ultrassônicos. Inicialização dos motores e da comunicação serial, se necessário para depuração.</p>

    <h3>2. Leitura dos Sensores:</h3>
    <ul>
        <li><strong>Sensor de Cor:</strong> O sensor de cor é lido constantemente para determinar a cor da superfície abaixo do robô. Baseado na cor detectada, o robô decide se deve seguir em frente, virar à esquerda ou à direita.</li>
        <li><strong>Sensores Ultrassônicos:</strong> Os sensores ultrassônicos medem a distância até os objetos à frente e aos lados. Se um objeto é detectado dentro de uma distância crítica, o robô ajusta seu trajeto para evitar a colisão.</li>
    </ul>

    <h3>3. Controle de Movimento:</h3>
    <ul>
        <li><strong>Seguindo a Linha:</strong>
            <ul>
                <li>Se a cor detectada é a da linha, o robô continua em frente.</li>
                <li>Se a cor detectada indica uma curva ou junção, o robô decide virar à esquerda ou à direita baseado nas cores pré-definidas para essas direções.</li>
            </ul>
        </li>
        <li><strong>Evitando Obstáculos:</strong>
            <ul>
                <li>Se um objeto é detectado à frente, o robô para ou desvia para evitar a colisão.</li>
                <li>Se um objeto é detectado ao lado, o robô ajusta sua trajetória para manter uma distância segura.</li>
            </ul>
        </li>
    </ul>

    <h3>4. Decisão de Direção:</h3>
    <p>Utilizando as informações do sensor de cor, o robô decide onde virar. Por exemplo, uma cor vermelha pode indicar uma curva à esquerda, enquanto uma cor azul pode indicar uma curva à direita.</p>
    </body>
</html>
