
import websockets
import keyboard
import asyncio
import pygame, math

IPADDRESS = "change_to_ip_address"
PORT = 8080

# global variables
mode = 'm'
best_angle = 0
lidar_data = [1200] * 360
counter = 0
retry = 0
last_direction = ''

# handler processes the message and sends "Success" back to the client
async def handler(websocket, path):
    global counter, lidar_data, retry, last_direction
    async for message in websocket:
        temp_list = message.split(",")
        angle_floored = (math.floor(float(temp_list[1]))) % 360
        lidar_data[angle_floored] = int(min([1200, max([300, float(temp_list[0])]) ])/2)
        GameUpdate()
        counter += 1
        if counter == 90:
            current_direction = checkKeys()
            if last_direction == current_direction and last_direction != 's':
                retry += 1
                if retry == 5:
                    if 'f' in last_direction:
                        current_direction = 'bbs'
                    else:
                        current_direction = 'fs'
                    retry = 0
            else:
                retry = 0
            print(retry)
            await websocket.send(current_direction)
            last_direction = current_direction
            counter = 0

pygame.init()
pygame.fastevent.init()

# Set up the drawing window
screen = pygame.display.set_mode([1200, 1200])
sysfont = pygame.font.get_default_font()
font1 = pygame.font.SysFont(sysfont, 72)

# run until the user asks to quit
running = True
# used to scale data to fit on the screen
max_distance = 0

def split(a, n):
    k, m = divmod(len(a), n)
    return (sum(a[i*k+min(i, m):(i+1)*k+min(i+1, m)]) for i in range(n))

def GameUpdate():

    global max_distance, running
    for event in pygame.fastevent.get():
        if event.type == pygame.QUIT:
            running = False

    screen.fill((20, 10, 30))
    pygame.draw.circle(screen, pygame.Color(100, 100, 120), (600, 600), 60)
    # Flip the display
    pygame.display.flip()
    for angle in range(360):
        if (mode == 'a') and best_angle == angle:
            pygame.draw.aaline(screen, (0,255,0), (600, 600), (line_positions[angle][0]+600, -line_positions[angle][1]+600), 4)
        else:
                distance = float(lidar_data[angle])
                radians = (90 - angle) * math.pi / 180.0
                x_axis = distance * math.cos(radians)
                y_axis = distance * math.sin(radians)
                pygame.draw.circle(screen, (255, 255, 255), (x_axis+600, 600-y_axis), 4)
    pygame.display.update()

def checkKeys():
    global mode
    if keyboard.is_pressed('a'):
        mode = 'a'
    elif keyboard.is_pressed('m'):
        mode = 'm'

    if mode == 'a':
        return directionAlgorithm()
    elif mode == 'm':
        if keyboard.is_pressed('up'):
            return 'fs'
        elif keyboard.is_pressed('down'):
            return 'bs'
        elif keyboard.is_pressed('left'):
            return 'ls'
        elif keyboard.is_pressed('right'):
            return 'rs'
        else:
            return 's'

def directionAlgorithm():
    global best_angle
    start = 15
    end = 45
    biggestSpace = [sum(lidar_data[-15:]) + sum((lidar_data[:15]))]
    for number in range(11):
        biggestSpace.append(sum(lidar_data[start:end]))
        start += 30
        end += 30
    best_angle = (biggestSpace.index(max(biggestSpace)) * 30) % 360
    if 345 <= best_angle <= 15:
        best_angle = 90
        return 'fs'
    elif 15 <= best_angle <= 50:
        best_angle = 45
        return 'rrfs'
    elif 50 <= best_angle <= 90:
        best_angle = 0
        return 'rrrfs'
    elif 90 <= best_angle <= 130:
        best_angle = 16
        return 'lllbs'
    elif 130 <= best_angle <= 165:
        best_angle = 80 #find
        return 'llbs'
    elif 165 <= best_angle <= 195:
        best_angle = 270
        return 'bs'
    elif 195 <= best_angle <= 230:
        best_angle = 15
        return 'rrbs'
    elif 230 <= best_angle <= 270:
        best_angle = 225 #find
        return 'rrrbs'
    elif 270 <= best_angle <= 315:
        best_angle = 180
        return 'lllfs'
    elif 315 <= best_angle <= 345:
        best_angle = 135
        return 'llfs'
    else:
        return 's'

def GenerateLinePositions(numberOfLines):
    angle = 360/numberOfLines
    lines = []
    for x in range(numberOfLines):
        radians = (90 - angle) * math.pi / 180.0
        lines.append([600 * math.cos((x)*radians), 600 * math.sin((x)*radians)])
        #lines.append([300 * math.sin((x)*angle/180 * math.pi), 300 * math.cos((x)*angle/180 * math.pi)])
    return lines

line_positions = GenerateLinePositions(360)

async def main():
    async with websockets.serve(handler, IPADDRESS, PORT, ping_interval=None):
        await asyncio.Future()  # run forever

if __name__ == "__main__":
    asyncio.run(main())