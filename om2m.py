from onem2m_func import *
uri_cse = "http://127.0.0.1:8080/~/in-cse/in-name"
ae = "Stepper Data"
cnt = "node1"

create_ae(uri_cse, ae)

uri_ae = uri_cse + "/" + ae
create_cnt(uri_ae, cnt)

uri_cnt = uri_ae + "/" + cnt
create_data_cin(uri_cnt, "ESW")

# delete(uri_cse, "FSR")
# delete(uri_cse, "Number_Of_Steps")
# delete(uri_cse, "EMG ")
