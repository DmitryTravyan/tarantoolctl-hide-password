# tarantoolctl-hide-password

# MacOs

## Cборка

```
gcc -Wall -shared -fPIC -undefined dynamic_lookup -o password.so src/password.c
```

Так же надо убедиться что `tarantool/include/` присутствует в `CPATH`, или вручную 
добавить путь в `package.cpath`.

```
chmod +x picodatactl
```

## Запуск

```
picodatactl connect localhost:3301
```

