import signal, sys, time

def handler(num, _):
    print('got:', sigmap.get(num, '<other>'))
    if num == signal.SIGINT:
        sys.exit(1)
    return 1

signames = ['SIGINT']
sigmap = dict((getattr(signal, k), k) for k in signames)
for name in signames:
    signal.signal(getattr(signal, name), handler)
while 1:
    time.sleep(1)