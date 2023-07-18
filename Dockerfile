FROM ubuntu:18.04
WORKDIR /opt/app

ADD . /opt/app

# タイムゾーンの設定
ENV TZ=Asia/Tokyo
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# ツールチェーンとC++testをPATHに設定する
ENV CPPTEST_MODULE=parasoft_cpptest_professional-2022.2.0-linux.x86_64.tar.gz
ENV CPPTEST_INS_DIR="/opt/app/cpptest"
ENV TOOL_CHAIN_DIR="/opt/app/gcc-arm-none-eabi-9-2019-q4-major/bin"
ENV PATH "${CPPTEST_INS_DIR}:${CPPTEST_INS_DIR}/bin:${TOOL_CHAIN_DIR}:$PATH"

# 一般的なツール群のインストール
RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y \
      build-essential \
      bzip2 \
      cmake \
      sudo \
      git \
      language-pack-ja-base \
      language-pack-ja \
      qemu-user-static \
      wget && \
    apt-get clean

RUN wget -qO- https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2019q4/gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux.tar.bz2 | tar -xj

# C++testのインストール
COPY ${CPPTEST_MODULE} /opt/app

RUN chmod u+rwx /opt/app/${CPPTEST_MODULE}
RUN tar zxvf /opt/app/${CPPTEST_MODULE} && \
    rm /opt/app/${CPPTEST_MODULE}

RUN chmod u+rwx -R ${CPPTEST_INS_DIR} && \
    chmod g+rwx -R ${CPPTEST_INS_DIR}

# language設定
RUN update-locale LANG=ja_JP.UTF-8

# ユーザーを追加
ARG DOCKER_UID=1000
ARG DOCKER_USER=cpptest
RUN useradd -m -u ${DOCKER_UID} ${DOCKER_USER}

ENV LC_ALL=ja_JP.UTF-8
