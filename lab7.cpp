// 6. Напишите программу с использованием MPI, моделирующую ситуацию: есть 2
// бригады по 20 рабочих (процессы). Каждый рабочий отсылает 1 сообщение-вопрос 
// каждому из рабочих другой бригады в строго заданном порядке, но может
// как получить, так и не получить ответ. Реализовать 5 кругов обмена
// сообщениями, то есть каждый рабочий должен отправить 95 сообщений-вопросов, 
// программа не должна попадать в ситуацию “deadlock”.