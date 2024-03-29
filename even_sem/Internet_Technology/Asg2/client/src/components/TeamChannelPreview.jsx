import React from "react";
import { Avatar, useChatContext } from "stream-chat-react";


// const TeamChannelPreview = ({ channel, type }) => {
const TeamChannelPreview = ({ setActiveChannel, setIsCreating, setIsEditing, setToggleContainer, channel, type }) => {
    const { channel: activeChannel, client } = useChatContext(); // Get the current state of the chat context => HOOKS

    const ChannelPreview = () => {
        return (
            <p className="channel-preview__item">
                # {channel?.data?.name || channel?.data?.id}
            </p>
        );
    };

    const DirectPreview = () => {
        // We're mapping over all the users and we're keeping only the ones whose ID != THE CLIENT ID
        // because THE CLIENT ID is our own ID, we're basically throwing ourselves outside of the chat
        // so that we can get the actual users we're talking to
        const members = Object.values(channel.state.members).filter(({ user }) => user.id !== client.userID);

        console.log(members[0]);

        return (
            <div className="channel-preview__item single">
                <Avatar 
                    image={members[0]?.user?.image}
                    name={members[0]?.user?.fullName || members[0]?.user?.id}
                    size={24}
                />
                <p>{members[0]?.user?.fullName || members[0]?.user?.id}</p>
            </div>
        )
    };

    return (
        <div className={
            channel?.id === activeChannel?.id
                ? "channel-preview__wrapper__selected"
                : "channel-preview__wrapper"
        }
            onClick={() => {
                setIsCreating(false);
                setIsEditing(false);
                setActiveChannel(channel);
                if (setToggleContainer) {
                    setToggleContainer((prevState) => !prevState)
                }
            }}
        >
            {type === "team" ? <ChannelPreview /> : <DirectPreview />}

        </div>
    );
};

export default TeamChannelPreview;
