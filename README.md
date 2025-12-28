# Projeto mc_project_01
Documentação Técnica – Microcontroladores AVR (ATmega328P)

Autor: ---
Plataforma alvo: ATmega328P (Arduino Uno / Nano)
Toolchain: AVR-GCC + CMake
Paradigma: Programação Bare Metal (sem Arduino Framework)

---------------------------------------------------------------------

## 1. Visão Geral do Projeto

O projeto **mc_project_01** é uma base estrutural para desenvolvimento de aplicações embarcadas em microcontroladores **AVR**, especificamente o **ATmega328P**, utilizando **C puro (ANSI C)** e **CMake** como sistema de build.

O objetivo principal deste projeto é:

- Fornecer uma **estrutura limpa e profissional**
- Evitar dependência do framework Arduino
- Permitir **controle total do hardware**
- Facilitar escalabilidade e manutenção
- Servir como base para projetos embarcados reais

Este projeto segue práticas típicas de desenvolvimento embarcado industrial.

---------------------------------------------------------------------

## 2. Arquitetura do Projeto

A estrutura de diretórios foi projetada para separar claramente:

- Código-fonte
- Cabeçalhos
- Sistema de build
- Configurações de toolchain
- Artefatos gerados

### 2.1 Estrutura de Diretórios

