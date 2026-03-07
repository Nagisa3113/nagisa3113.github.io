---
title: Arch Linux Setup
date: 2026-03-07
description: 记录一下Thinkpad-T14 Gen1安装ArchLinux+Hyprland的过程
---


## 安装前联网

iwctl
station wlan0 connect "wifi-name"



## 安装软件

sudo pacman -S \
amd-ucode \ 
pavucontrol \
sudo \
neovim
wayland \ 
pipewire wireplumber \
sudo \
git \
fish \
kitty \ 
wofi \ 
waybar \ 
hyprpaper \ 
hyprlock \ 
hypridle \
mako \
wl-clipboard \
hyprpolkitagent \
udiskie \
keyd \
firefox \
yazi \
xdg-desktop-portal-hyprland \ 
tlp \
mesa \
vulkan-radeon \
noto-fonts noto-fonts-cjk noto-fonts-emoji

## 一些配置
sudo ln -sf /usr/bin/nvim /usr/bin/vi
sudo ln -sf /usr/bin/nvim /usr/bin/vim

set -U fish_greeting

echo "nagisa ALL=(ALL) NOPASSWD:NOPASSWD:ALL" >> /etc/sudoers

## 系统启动项

systemctl --user enable --now pipewire wireplumber

sudo systemctl enable --now NetworkManager

tlp

sudo systemctl enable --now keyd

## 改键

- sudo nano /etc/keyd/default.conf

```
[ids]
*
[main]
backspace = backslash
backslash = backspace
capslock = leftcontrol
grave = escape
delete = grave
```

sudo systemctl restart keyd

## 安装后联网

nmcli device wifi list

nmcli device wifi connect "wifi-name" password "pwd"

## 壁纸

![wallpaper](/assets/img/posts/arch-linux/bloodborne.jpg)